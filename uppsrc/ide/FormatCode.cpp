#include "ide.h"

bool ReFormatJSON_XML(String& text, bool xml)
{
	if(xml) {
		try {
			XmlNode n = ParseXML(text);
			text = AsXML(n);
		}
		catch(XmlError) {
			Exclamation("Error passing the XML!");
			return false;
		}
	}
	else {
		Value v = ParseJSON(text);
		if(v.IsError()) {
			Exclamation("Error passing the JSON!");
			return false;
		}
		text = AsJSON(v, true);
	}
	return true;
}

void Ide::FormatJSON_XML(bool xml)
{
	int l, h;
	bool sel = editor.GetSelection(l, h);
	if((sel ? h - l : editor.GetLength()) > 75 * 1024 * 1024) {
		Exclamation("Too big to reformat");
		return;
	}
	String text;
	if(sel)
		text = editor.GetSelection();
	else {
		SaveFile();
		text = LoadFile(editfile);
	}
	if(!ReFormatJSON_XML(text, xml))
		return;
	editor.NextUndo();
	if(sel) {
		editor.Remove(l, h - l);
		editor.SetSelection(l, l + editor.Insert(l, text));
	}
	else {
		editor.Remove(0, editor.GetLength());
		editor.Insert(0, text);
	}
}

void Ide::FormatJSON() { FormatJSON_XML(false); }
void Ide::FormatXML() { FormatJSON_XML(true); }

String Ide::FindClangFormatPath()
{
	String p;
	auto Check = [&](const String& dir) {
		for(String fn : { ".clang-format", "_clang-format" }) {
			p = AppendFileName(dir, fn);
			if(FileExists(p))
				return true;
		}
		return false;
	};

	for(String dir = GetFileFolder(editfile); dir.GetCount() > 3; dir = GetFileFolder(dir))
		if(Check(dir))
			return p;
	
	for(String dir : GetUppDirs())
		if(Check(dir))
			return p;
	
	return Null;
}

String ClangFormatPath()
{
	return ConfigFile("clang_format");
}

VectorMap<String, String> ReadClangFormatFile(Stream& in)
{
	VectorMap<String, String> val;
	String master_id;
	while(!in.IsEof()) {
		String l = in.GetLine();
		String id;
		bool nested = findarg(*l, ' ', '\t') >= 0;
		CParser p(l);
		try {
			if(p.IsId()) {
				String id = p.ReadId();
				if(nested)
					id = master_id + ":" + id;
				else
					master_id = id;
				p.PassChar(':');
				String value = TrimBoth(p.GetPtr());
				int q = value.Find('#');
				if(q >= 0)
					value.Trim(q);
				value = TrimBoth(value);
				if(value.GetCount())
					val.GetAdd(id) = value;
			}
		}
		catch(CParser::Error) {
			continue;
		}
	}
	return val;
}

String ReformatCpp(CodeEditor& editor, bool setcursor)
{
	String clang_format_path = ClangFormatPath();
	FileIn in(clang_format_path);
	VectorMap<String, String> fv = ReadClangFormatFile(in);
	if(IsNull(fv.Get("BasedOnStyle", Null)))
		clang_format_path = TheIde()->FindClangFormatPath();
	int64 l, h;
	bool sel = editor.GetSelection(l, h);

	String cmd = "clang-format ";
	if(sel) {
		l = editor.GetLine(l) + 1;
		h = editor.GetLine(h) + 1;
		cmd << "--lines=" << l << ":" << h << " ";
	}

	String temp_path = CacheFile(AsString(Random()) + AsString(Random()) + "_to_format.cpp");
	{
		FileOut out(temp_path);
		editor.Save(out, CHARSET_UTF8, TextCtrl::LE_LF);
		if(out.IsError()) {
			Exclamation("Failed to save temporary file \1" + temp_path);
			return "Failed to save temporary file " + temp_path;
		}
	}

	cmd << "\"--style=file:" << clang_format_path << "\" ";
	
	String r;
	int code = Sys(cmd + temp_path, r);
	
	DeleteFile(temp_path);
	
	if(code) {
		if(code < 0)
			return "Failed to start clang-format";
		StringStream ss(r);
		String l;
		while(!ss.IsEof() && IsNull(l))
			l = ss.GetLine();
		int q = l.Find("error:");
		if(q >= 0 && q < r.GetCount() - 2)
			return TrimLeft(l.Mid(q + 6));
		return Nvl(l, "Unspecified error.");
	}

	Vector<String> ln = Split(r, '\n', false);
	for(String& s : ln)
		s.TrimEnd("\r");
	int n = editor.GetLineCount();
	l = h = n;
	for(int i = 0; i < n; i++)
		if(i >= ln.GetCount() || editor.GetUtf8Line(i) != ln[i]) {
			l = i;
			break;
		}
	for(int i = 0; i < n; i++)
		if(i >= ln.GetCount() || editor.GetUtf8Line(n - 1 - i) != ln[ln.GetCount() - 1 - i]) {
			h = i;
			break;
		}
	
	if(l + h >= n)
		return Null;
	
	editor.NextUndo();
	int from = editor.GetPos(l);
	editor.Remove(from, editor.GetPos(editor.GetLineCount() - h) - from);
	ln.Remove(0, l);
	ln.Trim(ln.GetCount() - h);
	int pos = editor.Insert(from, Join(ln, "\n") + "\n", CHARSET_UTF8);
	if(setcursor)
		editor.SetCursor(pos);
	
	return Null;
}

struct ClangFormat {
	const char *id;
	const char *type;
}
clang_format[] = {
	{ "AccessModifierOffset", "@" }, // int
	{ "AlignAfterOpenBracket", "Align:DontAlign:AlwaysBreak:BlockIndent" },
	{ "AlignArrayOfStructures", "Left:Right:None" },
	{ "AlignConsecutiveAssignments", "None:Consecutive:AcrossEmptyLines:AcrossComments:AcrossEmptyLinesAndComments" },
	{ "AlignConsecutiveBitFields", "None:Consecutive:AcrossEmptyLines:AcrossComments:AcrossEmptyLinesAndComments" },
	{ "AlignConsecutiveDeclarations", "None:Consecutive:AcrossEmptyLines:AcrossComments:AcrossEmptyLinesAndComments" },
	{ "AlignConsecutiveMacros", "None:Consecutive:AcrossEmptyLines:AcrossComments:AcrossEmptyLinesAndComments" },
	{ "AlignEscapedNewlines", "DontAlign:Left:Right" },
	{ "AlignOperands", "DontAlign:Align:AlignAfterOperator" },
	{ "AlignTrailingComments", "!" }, // bool
	{ "AllowAllArgumentsOnNextLine", "!" },
	{ "AllowAllConstructorInitializersOnNextLine", "!" },
	{ "AllowAllParametersOfDeclarationOnNextLine", "!" },
	{ "AllowShortBlocksOnASingleLine", "Never:Empty:Always" },
	{ "AllowShortCaseLabelsOnASingleLine", "!" },
	{ "AllowShortEnumsOnASingleLine", "!" },
	{ "AllowShortFunctionsOnASingleLine", "None:InlineOnly:Empty:Inline:All" },
	{ "AllowShortIfStatementsOnASingleLine", "Never:WithoutElse:OnlyFirstIf:AllIfsAndElse" },
	{ "AllowShortLambdasOnASingleLine", "None:Empty:Inline:All" },
	{ "AllowShortLoopsOnASingleLine", "!" },
	{ "AlwaysBreakAfterDefinitionReturnType", "None:All:TopLevel" },
	{ "AlwaysBreakAfterReturnType", "None:All:TopLevel:AllDefinitions:TopLevelDefinitions" },
	{ "AlwaysBreakBeforeMultilineStrings", "!" },
	{ "AlwaysBreakTemplateDeclarations", "No:MultiLine:Yes" },
	{ "BinPackArguments", "!" },
	{ "BinPackParameters", "!" },
	{ "BitFieldColonSpacing", "Both:None:Before:After" },
	{ "BraceWrapping", "" },
	{ " AfterCaseLabel", "!" },
	{ " AfterControlStatement", "Never:MultiLine:Always" },
	{ " AfterEnum","!" },
	{ " AfterFunction","!" },
	{ " AfterNamespace","!" },
	{ " AfterObjCDeclaration","!" },
	{ " AfterStruct","!" },
	{ " AfterUnion","!" },
	{ " AfterExternBlock","!" },
	{ " BeforeCatch","!" },
	{ " BeforeElse","!" },
	{ " BeforeLambdaBody","!" },
	{ " BeforeWhile","!" },
	{ " IndentBraces","!" },
	{ " SplitEmptyFunction","!" },
	{ " SplitEmptyRecord","!" },
	{ " SplitEmptyNamespace","!" },
	{ "BreakAfterAttributes", "Always:Leave:Never" },
	{ "BreakBeforeBinaryOperators", "None:NonAssignment:All" },
	{ "BreakBeforeBraces", "Attach:Linux:Mozilla:Stroustrup:Allman:Whitesmiths:GNU:WebKit:Custom" },
	{ "BreakBeforeConceptDeclarations", "Never:Allowed:Always" },
	{ "BreakBeforeInlineASMColon", "Never:OnlyMultiline:Always" },
	{ "BreakBeforeTernaryOperators", "!" },
	{ "BreakConstructorInitializers", "BeforeColon:BeforeComma:AfterColon" },
	{ "BreakInheritanceList", "BeforeColon:BeforeComma:AfterColon:AfterComma" },
	{ "BreakStringLiterals", "!" },
	{ "ColumnLimit", "#" }, // unsigned
	{ "CompactNamespaces", "!" },
	{ "ConstructorInitializerIndentWidth", "#" },
	{ "ContinuationIndentWidth", "#" },
	{ "Cpp11BracedListStyle", "!" },
	{ "DeriveLineEnding", "!" },
	{ "DerivePointerAlignment", "!" },
	{ "DisableFormat", "!" },
	{ "EmptyLineAfterAccessModifier", "Never:Leave:Always" },
	{ "EmptyLineBeforeAccessModifier", "Never:Leave:LogicalBlock:Always" },
	{ "ExperimentalAutoDetectBinPacking", "!" },
	{ "FixNamespaceComments", "!" },
	{ "IndentAccessModifiers", "!" },
	{ "IndentCaseBlocks", "!" },
	{ "IndentCaseLabels", "!" },
	{ "IndentExternBlock", "AfterExternBlock:NoIndent:Indent" },
	{ "IndentGotoLabels", "!" },
	{ "IndentPPDirectives", "None:AfterHash:BeforeHash" },
	{ "IndentRequiresClause", "!" },
	{ "IndentWidth", "#" },
	{ "IndentWrappedFunctionNames", "!" },
	{ "InsertBraces", "!" },
	{ "InsertNewlineAtEOF", "!" },
	{ "InsertTrailingCommas", "None:Wrapped" },
	{ "IntegerLiteralSeparator", "" },
	{ " Decimal", "@" },
	{ " Hex", "@" },
	{ " Binary", "@" },
	{ "KeepEmptyLinesAtTheStartOfBlocks", "!" },
	{ "LambdaBodyIndentation", "Signature:OuterScope" },
	{ "MaxEmptyLinesToKeep", "#" },
	{ "NamespaceIndentation", "None:Inner:All" },
	{ "PPIndentWidth", "@" },
	{ "PackConstructorInitializers", "Never:BinPack:CurrentLine:NextLine" },
	{ "PenaltyBreakAssignment", "#" },
	{ "PenaltyBreakBeforeFirstCallParameter", "#" },
	{ "PenaltyBreakComment", "#" },
	{ "PenaltyBreakFirstLessLess", "#" },
	{ "PenaltyBreakOpenParenthesis", "#" },
	{ "PenaltyBreakString", "#" },
	{ "PenaltyBreakTemplateDeclaration", "#" },
	{ "PenaltyExcessCharacter", "#" },
	{ "PenaltyIndentedWhitespace", "#" },
	{ "PenaltyReturnTypeOnItsOwnLine", "#" },
	{ "PointerAlignment", "Left:Right:Middle" },
	{ "QualifierAlignment", "Leave:Left:Right:Custom" },
	{ "ReferenceAlignment", "Pointer:Left:Right:Middle" },
	{ "ReflowComments", "!" },
	{ "RemoveBracesLLVM", "!" },
	{ "RemoveSemicolon", "!" },
	{ "RequiresClausePosition", "OwnLine:WithPreceding:WithFollowing:SingleLine" },
	{ "RequiresExpressionIndentation", "OuterScope:Keyword" },
	{ "SeparateDefinitionBlocks", "Leave:Always:Never" },
	{ "ShortNamespaceLines", "#" },
	{ "SortIncludes", "Never:CaseSensitive:CaseInsensitive" },
	{ "SortUsingDeclarations", "Never:Lexicographic:LexicographicNumeric" },
	{ "SpaceAfterCStyleCast", "!" },
	{ "SpaceAfterLogicalNot", "!" },
	{ "SpaceAfterTemplateKeyword", "!" },
	{ "SpaceAroundPointerQualifiers", "Default:Before:After:Both" },
	{ "SpaceBeforeAssignmentOperators", "!" },
	{ "SpaceBeforeCaseColon", "!" },
	{ "SpaceBeforeCpp11BracedList", "!" },
	{ "SpaceBeforeCtorInitializerColon", "!" },
	{ "SpaceBeforeInheritanceColon", "!" },
	{ "SpaceBeforeParens", "Never:ControlStatements:ControlStatementsExceptControlMacros:NonEmptyParentheses:Always:Custom" },
	{ "SpaceBeforeParensOptions", "" },
	{ " AfterControlStatements", "!" },
	{ " AfterForeachMacros", "!" },
	{ " AfterFunctionDeclarationName", "!" },
	{ " AfterFunctionDefinitionName", "!" },
	{ " AfterIfMacros", "!" },
	{ " AfterOverloadedOperator", "!" },
	{ " AfterRequiresInClause", "!" },
	{ " AfterRequiresInExpression", "!" },
	{ " BeforeNonEmptyParentheses", "!" },
	{ "SpaceBeforeRangeBasedForLoopColon", "!" },
	{ "SpaceBeforeSquareBrackets", "!" },
	{ "SpaceInEmptyBlock", "!" },
	{ "SpaceInEmptyParentheses", "!" },
	{ "SpacesBeforeTrailingComments", "#" },
	{ "SpacesInAngles", "Never:Always:Leave" },
	{ "SpacesInCStyleCastParentheses", "!" },
	{ "SpacesInConditionalStatement", "!" },
	{ "SpacesInContainerLiterals", "!" },
	{ "SpacesInLineCommentPrefix", "" },
	{ " Minimum", "#" },
	{ " Maximum", "#" },
	{ "SpacesInParentheses", "!" },
	{ "SpacesInSquareBrackets", "!" },
	{ "TabWidth", "#" },
	{ "UseTab", "Never:ForIndentation:ForContinuationAndIndentation:AlignWithSpaces:Always" },
#ifdef _DEBUG
	{ "Test", "Never:ForIndentation:ForContinuationAndIndentation:AlignWithSpaces:Always" },
#endif
};

struct ReformatDlg : WithReformatLayout<TopWindow> {
	String editfile;
	String code;
	bool   sel;
	int    l, h;

	Array<Ctrl>  option;
	Array<Label> lbl;
	ParentCtrl   soptions;
	int          scy;
	ScrollBar    sb;
	

	virtual void Layout() override;
	virtual void MouseWheel(Point p, int zdelta, dword keyflags) override;

	void   Set(LineEdit& editor);
	void   Sync();
	String Get();
	void   Set(Stream& in);

	ReformatDlg();
	~ReformatDlg();
};

ReformatDlg::ReformatDlg()
{
	CtrlLayoutOKCancel(*this, "Reformat");
	view.Highlight("cpp");
	view.HideBar();
	view.SetFont(CourierZ(12));
	view.ShowSpaces();
	view.ShowTabs();
	view.SetReadOnly();

	String p = TheIde()->FindClangFormatPath();
	if(p.GetCount())
		base.Add(Null, ".clang-format file " + p);
	for(String id : { "LLVM", "Google", "Chromium", "Mozilla", "WebKit", "Microsoft", "GNU" })
		base.Add("BasedOnStyle: " + id, "Based on style " + id);
	base << [=] { Sync(); };
	base.SetIndex(0);
	
	int cy = EditField::GetStdHeight();
	int y = 0;
	int lw = 0;
	for(const ClangFormat& f : clang_format)
		if(f.type && *f.type != '!')
			lw = max(lw, GetTextSize(f.id, StdFont().Bold()).cx + DPI(4) + (*f.id == ' ') * DPI(20));
	for(const ClangFormat& f : clang_format) {
		int x = 0;
		String id = f.id;
		if(*id == ' ') {
			id = id.Mid(1);
			x = DPI(20);
		}
		if(f.type && *f.type == '!') {
			Option& o = option.Create<Option>();
			o.ThreeState();
			o.SetLabel(id);
			o <<= Null;
			o << [=] { Sync(); };
			soptions << o.HSizePos(x, DPI(2)).TopPos(y, cy);
		}
		else {
			Label& l = lbl.Create<Label>();
			l.SetLabel(id);
			soptions << l.LeftPos(x, Zx(200)).TopPos(y, cy);
			if(f.type) {
				if(*f.type == '#' || *f.type == '@') {
					WithDropChoice<EditIntSpin>& e = option.Create<WithDropChoice<EditIntSpin>>();
					e.MinMax(*f.type == '@' ? -100 : 0, 100);
					for(int q = *f.type == '@' ? -8 : 0; q <= 8; q++)
						e.AddList(q);
					e.NullText("default");
					e << [=] { Sync(); };
					soptions << e.HSizePos(lw, DPI(2)).TopPos(y, cy);
				}
				else
				if(*f.type) {
					DropList& dl = option.Create<DropList>();
					dl.Add(Null, AttrText("default").Italic().NormalInk(SCyan()));
					for(const String& s : Split(f.type, ':'))
						dl.Add(s);
					dl << [=] { Sync(); };
					soptions << dl.HSizePos(lw, DPI(2)).TopPos(y, cy);
				}
			}
		}
		y += cy + DPI(2);
	}
	sb.SetTotal(y);
	
	options.SetFrame(ViewFrame());
	options.AddFrame(sb);
	options << soptions.HSizePos().TopPos(0, sb.GetTotal());
	
	sb << [=] {
		soptions.TopPos(-sb, sb.GetTotal());
	};
	
	save << [=] {
		SelectSaveFile("All files\t*.*", Get());
	};
	
	load << [=] {
		SelectFileIn in("All files\t*.*");
		Set(in);
	};
	
	clear << [=] {
		if(PromptYesNo("Set all options to default?")) {
			for(Ctrl& q : option)
				q <<= Null;
			Sync();
		}
	};
	
	FileIn in(ClangFormatPath());
	Set(in);
}

ReformatDlg::~ReformatDlg()
{
	Sync();
}

void ReformatDlg::MouseWheel(Point, int zdelta, dword)
{
	sb.Wheel(zdelta, EditField::GetStdHeight() + DPI(2));
}

void ReformatDlg::Set(Stream& in)
{
	VectorMap<String, String> val = ReadClangFormatFile(in);
	String s = val.Get("BasedOnStyle", Null);
	if(s.GetCount()) {
		s = "BasedOnStyle: " + s;
		if(base.HasKey(s))
			base <<= s;
	}
	else
		base.SetIndex(0);
	
	int ii = 0;
	String master_id;
	for(const ClangFormat& f : clang_format) {
		int x = 0;
		String id = f.id;
		if(*id == ' ')
			id = master_id + ":" + TrimBoth(id);
		else
			master_id = id;
		
		String v = val.Get(id, Null);
		if(f.type && *f.type) {
			Ctrl& o = option[ii++];
			o <<= Null;
			if(v.GetCount()) {
				if(*f.type == '!')
					o <<= decode(v, "true", true, "false", false, Null);
				else
				if(findarg(*f.type, '@', '#') >= 0)
					o <<= StrInt(v);
				else {
					DropList *l = dynamic_cast<DropList *>(&o);
					if(l && l->HasKey(v))
						*l <<= v;
				}
			}
		}
	}
}

String ReformatDlg::Get()
{
	String out;
	out << "Language: Cpp\n";
	out << ~base << "\n";
	int ii = 0;
	String master_id;
	for(const ClangFormat& f : clang_format) {
		String value;
		if(f.type && *f.type) {
			value = ~~option[ii++];
			if(*f.type == '!')
				value = decode(value, "1", "true", "0", "false", "");
		}
		else
			master_id = f.id;
		if(value.GetCount()) {
			if(*f.id == ' ') {
				if(master_id.GetCount()) {
					out << master_id << ":\n";
					master_id.Clear();
				}
				out << " ";
			}
			out << f.id << ": " << value << "\n";
		}
	}
	return out;
}

void ReformatDlg::Layout()
{
	sb.SetPage(options.GetSize().cy);
}

void ReformatDlg::Sync()
{
	view.Set(code, CHARSET_UTF8);
	view.ClearSelection();
	if(sel)
		view.SetSelection(l, h);
	
	Upp::SaveFile(ClangFormatPath(), Get());
	
	String err = ReformatCpp(view, false);
	if(IsNull(err)) {
		error.SetLabel("");
		ok.Enable();
	}
	else {
		error.SetLabel("Clang-format has failed: " + Filter(err, CharFilterNoCrLf));
		ok.Disable();
	}
	
	for(Ctrl& q : option)
		q.Enable(!IsNull(base));

	for(Label& q : lbl)
		q.SetInk(IsNull(base) ? SColorDisabled() : SColorText());

	view.SetCursor(l);

	int ii = 0;
	int li = 0;
	for(const ClangFormat& f : clang_format) {
		if(f.type && *f.type == '!') {
			Option *o = dynamic_cast<Option *>(&option[ii++]);
			o->SetFont(IsNull(*o) ? StdFont() : StdFont().Bold());
		}
		else {
			Label& l = lbl[li++];
			if(f.type && *f.type) {
				Ctrl& c = option[ii++];
				l.SetFont(IsNull(c) ? StdFont() : StdFont().Bold());
			}
		}
	}
}

void ReformatDlg::Set(LineEdit& editor)
{
	sel = editor.GetSelection(l, h);
	code = editor.Get(CHARSET_UTF8);
}

void Ide::ReformatCodeDlg()
{
	ReformatDlg dlg;
	dlg.editfile = editfile;
	dlg.Set(editor);
	dlg.Sync();

	if(dlg.Execute() == IDOK) {
		String error = ReformatCpp(editor, true);
		if(error.GetCount())
			PromptOK("clang-format has failed:&\1" + error);
	}
}

void Ide::ReformatCode()
{
	String clang_format_path = FindClangFormatPath();

	if(IsNull(clang_format_path)) {
		ReformatCodeDlg();
		return;
	}

	if(ReformatCpp(editor, true).GetCount())
		ReformatCodeDlg();
}

void Ide::ReformatComment() { editor.ReformatComment(); }
