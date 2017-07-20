topic "Tutorial";
[2 $$0,0#00000000000000000000000000000000:Default]
[l288;i1120;a17;O9;~~~.1408;2 $$1,0#10431211400427159095818037425705:param]
[a83;*R6 $$2,5#31310162474203024125188417583966:caption]
[H4;b83;*4 $$3,5#07864147445237544204411237157677:title]
[i288;O9;C2 $$4,6#40027414424643823182269349404212:item]
[b42;a42;ph2 $$5,5#45413000475342174754091244180557:text]
[l288;b17;a17;2 $$6,6#27521748481378242620020725143825:desc]
[l321;C@5;1 $$7,7#20902679421464641399138805415013:code]
[b2503;2 $$8,0#65142375456100023862071332075487:separator]
[*@(0.0.255)2 $$9,0#83433469410354161042741608181528:base]
[C2 $$10,0#37138531426314131251341829483380:class]
[l288;a17;*1 $$11,11#70004532496200323422659154056402:requirement]
[i417;b42;a42;O9;~~~.416;2 $$12,12#10566046415157235020018451313112:tparam]
[b167;C2 $$13,13#92430459443460461911108080531343:item1]
[i288;a42;O9;C2 $$14,14#77422149456609303542238260500223:item2]
[*@2$(0.128.128)2 $$15,15#34511555403152284025741354420178:NewsDate]
[l321;*C$7;2 $$16,16#03451589433145915344929335295360:result]
[l321;b83;a83;*C$7;2 $$17,17#07531550463529505371228428965313:result`-line]
[l160;*C+117 $$18,5#88603949442205825958800053222425:package`-title]
[2 $$19,0#53580023442335529039900623488521:gap]
[C2 $$20,20#70211524482531209251820423858195:class`-nested]
[b50;2 $$21,21#03324558446220344731010354752573:Par]
[{_}%EN-US 
[s2; Skylark Tutorial&]
[s3; Table of contents&]
[s0; &]
[s0; [^topic`:`/`/Skylark`/srcdoc`/Tutorial`$en`-us`#1^ 1. SKYLARK 
handlers and path patterns]&]
[s0; [^topic`:`/`/Skylark`/srcdoc`/Tutorial`$en`-us`#2^ 2. Witz templates]&]
[s0; [^topic`:`/`/Skylark`/srcdoc`/Tutorial`$en`-us`#3^ 3. Witz links 
to handlers]&]
[s0; [^topic`:`/`/Skylark`/srcdoc`/Tutorial`$en`-us`#4^ 4. Combining 
Witz templates using #define and #include]&]
[s0; [^topic`:`/`/Skylark`/srcdoc`/Tutorial`$en`-us`#5^ 5. FORM GET]&]
[s0; [^topic`:`/`/Skylark`/srcdoc`/Tutorial`$en`-us`#6^ 6. FORM POST]&]
[s0; [^topic`:`/`/Skylark`/srcdoc`/Tutorial`$en`-us`#7^ 7. Session 
variables]&]
[s0; [^topic`:`/`/Skylark`/srcdoc`/Tutorial`$en`-us`#8^ 8. Ajax support]&]
[s0; [^topic`:`/`/Skylark`/srcdoc`/Tutorial`$en`-us`#9^ 9. Connecting 
SQL database]&]
[s0; [^topic`:`/`/Skylark`/srcdoc`/Tutorial`$en`-us`#10^ 10. Advanced 
SQL]&]
[s0; [^topic`:`/`/Skylark`/srcdoc`/Tutorial`$en`-us`#11^ 11. Language 
support]&]
[s0; [^topic`:`/`/Skylark`/srcdoc`/Tutorial`$en`-us`#12^ 12. Packs]&]
[s0; &]
[s3;:1: 1. SKYLARK handlers and path patterns&]
[s5; Skylark application is divided to `'handlers`' which provide 
response to various HTTP requests based on url pattern:&]
[s7; &]
[s7; #include <Skylark/Skylark.h>&]
[s7; &]
[s7; using namespace Upp;&]
[s7; &]
[s7; [* SKYLARK](HomePage, `"`")&]
[s7; `{&]
[s7; -|http << `"<!DOCTYPE html><html><body>Hello world!</body></html>`";&]
[s7; `}&]
[s7; &]
[s7; [* SKYLARK](Param, `"`*/param`")&]
[s7; `{&]
[s7; -|http << `"<!DOCTYPE html><html><body>Parameter: `" << http`[0`] 
<< `"</html></body>`";&]
[s7; `}&]
[s7; &]
[s7; [* SKYLARK](Params, `"params/`*`*`")&]
[s7; `{&]
[s7; -|http << `"<!DOCTYPE html><html><body>Parameters: `";&]
[s7; -|for(int i `= 0; i < http.GetParamCount(); i`+`+)&]
[s7; -|-|http << http`[i`] << `" `";&]
[s7; -|http << `"</html></body>`";&]
[s7; `}&]
[s7; &]
[s7; [* SKYLARK](CatchAll, `"`*`*`")&]
[s7; `{&]
[s7; -|http.[* Redirect](HomePage);&]
[s7; `}&]
[s7; &]
[s7; [* SKYLARK](Favicon, `"/favicon.ico`")&]
[s7; `{&]
[s7; -|http.ContentType(`"image/png`") << LoadFile(GetDataFile(`"favicon.png`"));&]
[s7; `}&]
[s7; &]
[s7; struct MyApp : SkylarkApp `{&]
[s7; -|MyApp() `{&]
[s7; -|-|[* root `= `"myapp`";]&]
[s7; -|#ifdef `_DEBUG&]
[s7; -|-|prefork `= 0;&]
[s7; -|-|use`_caching `= false;&]
[s7; -|#endif&]
[s7; -|`}&]
[s7; `};&]
[s7; &]
[s7; CONSOLE`_APP`_MAIN&]
[s7; `{&]
[s7; #ifdef `_DEBUG&]
[s7; -|StdLogSetup(LOG`_FILE`|LOG`_COUT);&]
[s7; -|Ini`::skylark`_log `= true;&]
[s7; #endif&]
[s7; &]
[s7; -|[* MyApp().Run();]-|&]
[s7; `}&]
[s7; &]
[s5; Handlers are introduced by macro [@5 SKYLARK], first parameters 
is the name of handler (macro creates a function that is named 
this way and this id is also used in various places like page 
templates) and path pattern which handler is supposed to respond 
to.&]
[s5; Handler is represented by C`+`+ function with single parameter 
Http`& [/ http], which is used for request processing. [@5 SKYLARK] 
macro creates a header for this function and also registers it 
with Skylark so that requestes matching the path pattern are 
dispatched to this function. Important note: as [@5 SKYLARK] macro 
uses global constructors to register handlers, handlers should 
be put into .icpp files (unless they are in the same file with 
`'main`').&]
[s5; Path pattern can contain parameter placeholders `'`*`' (see 
[@5 Param] handler), which are then provided by [/ http] as parameters 
(through operator`[`](int)). Path is always split by `'/`' characters 
and each part must either be text or placeholder `- patterns 
like `"something`*/to`*avoid`" are not allowed&]
[s5; Special wildcard `'`*`*`' represents any other number of placeholders 
(see [@5 Params]); in special case it is useful to catch all unresolved 
requests to website and [@5 Redirect] them to the application homepage 
(see [@5 CatchAll]).&]
[s5; The priority of various handlers for particular request is determined 
by number of text parts matched, which means that for request 
`"foo/bar/32`" placeholder `"foo/bar/`*`" has priority over `"foo/`*/`*`".&]
[s5; Another concern is setting of root path for application, in 
code above done by `"[* root ]`= `"[@3 myapp]`";`". This defines 
the root path of application, in other words [@5 HomePage ]handler 
will react to `"[@3 myapp]`" path, Param handler to e.g. `"[@3 myapp]/test/param`" 
etc. In situation where this is not desirable, it is possible 
to exclude root by adding `'/`' at the start of path, as demonstrated 
by [@5 Favicon] handler.&]
[s5; [@5 MyApp().Run()] starts a HTTP server (and also SCGI server) 
on default port 8001, so after starting application, you should 
be able to access it from your browser by entering &]
[s5; 127.0.0.1:8001/myapp&]
[s5; We then recommend to try e.g.&]
[s0; 127.0.0.1:8001/myapp/anything/param&]
[s0; 127.0.0.1:8001/myapp/params/1/2/3&]
[s0; 127.0.0.1:8001/myapp/anythingelse&]
[s0; 127.0.0.1:8001&]
[s5; Last one should result in error `"Page not found`", as no matching 
handler is present.&]
[s5; &]
[s3;:2: 2. Witz templates&]
[s5; To decouple presentation layer from application logic, Skylark 
features template language `'Witz`':&]
[s7; &]
[s7; #include <Skylark/Skylark.h>&]
[s7; &]
[s7; using namespace Upp;&]
[s7; &]
[s7; SKYLARK(HomePage, `"`")&]
[s7; `{&]
[s7; -|ValueArray va;&]
[s7; -|va.Add(1);&]
[s7; -|va.Add(`"Hello`");&]
[s7; -|ValueMap m;&]
[s7; -|m.Add(`"key1`", `"first value`");&]
[s7; -|m.Add(`"key2`", `"second value`");&]
[s7; &]
[s7; -|[* http(`"MyValue`", `"some value`")]&]
[s7; [* -|    (`"MyRawValue`", Raw(`"<b>raw <u>html</u></b>`"))]&]
[s7; [* -|    (`"MyRawValue2`", `"<b>another raw <u>html</u></b>`")]&]
[s7; [* -|    (`"MyArray`", va)]&]
[s7; [* -|    (`"MyMap`", m)]&]
[s7; [* -|    .RenderResult(`"Skylark02/index`");]&]
[s7; `}&]
[s7; &]
[s7; struct MyApp : SkylarkApp `{&]
[s7; -|MyApp() `{&]
[s7; -|-|root `= `"myapp`";&]
[s7; -|#ifdef `_DEBUG&]
[s7; -|-|prefork `= 0;&]
[s7; -|-|[* use`_caching ]`= false;&]
[s7; -|#endif&]
[s7; -|`}&]
[s7; `};&]
[s7; &]
[s7; CONSOLE`_APP`_MAIN&]
[s7; `{&]
[s7; #ifdef `_DEBUG&]
[s7; -|StdLogSetup(LOG`_FILE`|LOG`_COUT);&]
[s7; -|Ini`::skylark`_log `= true;&]
[s7; #endif&]
[s7; &]
[s7; -|MyApp().Run();-|&]
[s7; `}&]
[s7; &]
[s7; &]
[s5; [* Skylark02/index.witz:]&]
[s7; &]
[s7; <!DOCTYPE html>&]
[s7; <html>&]
[s7; <body>&]
[s7; MyValue: [* `$MyValue]<br>&]
[s7; MyRawValue: [* `$MyRawValue]<br>&]
[s7; MyRawValue2: [* `$raw(MyRawValue2)]<br>&]
[s7; <br>MyArray:<br>&]
[s7; [* `$for(i in MyArray)]&]
[s7; [* -|`$i.`_index. `$i<br>]&]
[s7; [* `$endfor]&]
[s7; <br>MyMap:<br>&]
[s7; [* `$for(i in MyMap)]&]
[s7; [* -|`$i.`_index. `$i.`_key: `$i<br>]&]
[s7; [* `$endfor]&]
[s7; </body>&]
[s7; </html>&]
[s7; &]
[s5; Witz template language loosely ressembles JavaScript. It is 
able to evaluate expression, supports `"if`" and looping through 
arrays or maps with `"for`".&]
[s5; Witz templates are compiled at runtime. Settings configuration 
variable [* use`_caching] to false makes them to compile each time 
they are invoked (otherwise the compilation result is cached) 
`- this is usefull while debugging, as templates can be adjusted 
while application is running.&]
[s5; The search path for templates is set by another configuration 
variable [* path]. Default value of [* path] is set to environment 
variable `'UPP`_ASSEMBLY`_`_`', which is set by theide to current 
assembly path `- which means that for debugging you do not need 
to worry about [* path] as long as all templates are in U`+`+ packages 
and you start the application from theide. Note that [* path] is 
also used to search for static files.&]
[s5; String values are normally HTML escaped; if you need to pass 
raw html code as parameter, you have to either use [@5 Raw ]C`+`+ 
function in application logic or [@5 raw] function in Witz.&]
[s5; &]
[s3;:3: 3. Witz links to handlers&]
[s5; Skylark handlers are represented in witz templates as function 
calls or simple variables with the same identifiers as the id 
of handler; both yield `" quoted path that matches the handler 
path pattern. If pattern contains parameter placeholder, it is 
passed as argument of the function:&]
[s7; &]
[s7; #include <Skylark/Skylark.h>&]
[s7; &]
[s7; using namespace Upp;&]
[s7; &]
[s7; SKYLARK([* HomePage], `"`")&]
[s7; `{&]
[s7; -|http.RenderResult(`"Skylark03/index`");&]
[s7; `}&]
[s7; &]
[s7; SKYLARK([* Page2], `"page2`")&]
[s7; `{&]
[s7; -|http.RenderResult(`"Skylark03/page2`");&]
[s7; `}&]
[s7; &]
[s7; SKYLARK([* Param], `"paramtest/`*`")&]
[s7; `{&]
[s7; -|http(`"PARAM`", http`[0`]).RenderResult(`"Skylark03/param`");&]
[s7; `}&]
[s7; &]
[s7; struct MyApp : SkylarkApp `{&]
[s7; -|MyApp() `{&]
[s7; -|-|root `= `"myapp`";&]
[s7; -|#ifdef `_DEBUG&]
[s7; -|-|prefork `= 0;&]
[s7; -|-|use`_caching `= false;&]
[s7; -|#endif&]
[s7; -|`}&]
[s7; `};&]
[s7; &]
[s7; CONSOLE`_APP`_MAIN&]
[s7; `{&]
[s7; #ifdef `_DEBUG&]
[s7; -|StdLogSetup(LOG`_FILE`|LOG`_COUT);&]
[s7; -|Ini`::skylark`_log `= true;&]
[s7; #endif&]
[s7; &]
[s7; -|MyApp().Run();-|&]
[s7; `}&]
[s7; &]
[s5; [* Skylark03/index.witz:]&]
[s7; &]
[s7; <!DOCTYPE html>&]
[s7; <html>&]
[s7; <body>&]
[s7; <a href`=[* `$Page2]>Link to page2</a><br>&]
[s7; `$for(i in `[`"param`_test`", 123, `"param`_test3`"`])&]
[s7; -|<a href`=[* `$Param(i)]>Param test: `$i</a><br>&]
[s7; `$endfor&]
[s7; </body>&]
[s7; </html>&]
[s7; &]
[s5; [* Skylark03/page2.witz:]&]
[s7; &]
[s7; <!DOCTYPE html>&]
[s7; <html>&]
[s7; <body>&]
[s7; <a href`=[* `$HomePage()]>Back to index</a><br>&]
[s7; </body>&]
[s7; </html>&]
[s7; &]
[s5; [* Skylark03/index.witz:]&]
[s7; &]
[s7; <!DOCTYPE html>&]
[s7; <html>&]
[s7; <body>&]
[s7; <a href`=[* `$Page2()]>Link to page2</a><br>&]
[s7; `$for(i in `[`"param`_test`", 123, `"param`_test3`"`])&]
[s7; -|<a href`=[* `$Param(i)]>Param test: `$i</a><br>&]
[s7; `$endfor&]
[s7; </body>&]
[s7; </html>&]
[s7; &]
[s5; &]
[s3;:4: 4. Combining Witz templates using #define and #include&]
[s5; Witz templates can be parametrized using subblock [@5 #define] 
[/@5 id] and [@5 #][/@5 id] insertion and combined from several files 
using [@5 #include]:&]
[s5; [* Skylark04/base.witz:]&]
[s7; &]
[s7; <!DOCTYPE html>&]
[s7; <html>&]
[s7; <title>#TITLE</title>&]
[s7; <body>&]
[s7; #BODY&]
[s7; </body>&]
[s7; </html>&]
[s7; &]
[s7; #define TITLE Generic title&]
[s7; &]
[s5; [* Skylark04/index.witz:]&]
[s7; &]
[s7; #include Skylark04/base&]
[s7; &]
[s7; #define TITLE MyApp title&]
[s7; &]
[s7; #define BODY&]
[s7; This is MyApp body html!&]
[s7; &]
[s5; &]
[s3;:5: 5. FORM GET&]
[s5; Whenever Skylark founds `'?`' sign in the request path, it converts 
attached values into http`'s [/ shared variable space], which is 
accessible using [* operator`[`]].&]
[s7; &]
[s7; #include <Skylark/Skylark.h>&]
[s7; &]
[s7; using namespace Upp;&]
[s7; &]
[s7; SKYLARK(HomePage, `"`")&]
[s7; `{&]
[s7; -|http.RenderResult(`"Skylark05/index`");&]
[s7; `}&]
[s7; &]
[s7; SKYLARK([* Submit], `"submit`")&]
[s7; `{&]
[s7; -|http(`"[* RESULT]`", ToUpper((String)[* http`[`"id`"`]]))&]
[s7; -|-|.RenderResult(`"Skylark05/submit`");&]
[s7; `}&]
[s7; &]
[s7; struct MyApp : SkylarkApp `{&]
[s7; -|MyApp() `{&]
[s7; -|-|root `= `"myapp`";&]
[s7; -|#ifdef `_DEBUG&]
[s7; -|-|prefork `= 0;&]
[s7; -|-|use`_caching `= false;&]
[s7; -|#endif&]
[s7; -|`}&]
[s7; `};&]
[s7; &]
[s7; CONSOLE`_APP`_MAIN&]
[s7; `{&]
[s7; #ifdef `_DEBUG&]
[s7; -|StdLogSetup(LOG`_FILE`|LOG`_COUT);&]
[s7; -|Ini`::skylark`_log `= true;&]
[s7; #endif&]
[s7; &]
[s7; -|MyApp().Run();-|&]
[s7; `}&]
[s7; &]
[s5; [* Skylark05/index.witz]&]
[s7; &]
[s7; <!DOCTYPE html>&]
[s7; <html>&]
[s7; <body>&]
[s7; <form action`=[* `$Submit] method`=`"[* get]`" accept`-charset`=`"utf`-8`" 
enctype`=`"multipart/form`-data`">&]
[s7;    <P>&]
[s7;     <INPUT type`=`"text`" name`=`"[* id]`">&]
[s7;     <INPUT type`=`"submit`" value`=`"Submit`">&]
[s7;    </P>&]
[s7; </form>&]
[s7; </body>&]
[s7; </html>&]
[s7; &]
[s5; [* Skylark05/submit.witz]&]
[s7; &]
[s7; <!DOCTYPE html>&]
[s7; <html>&]
[s7; <body>&]
[s7; Result: [* `$RESULT]<br>&]
[s7; <a href`=`$HomePage>Back to homepage</a>&]
[s7; </body>&]
[s7; </html>&]
[s7; &]
[s5; &]
[s3;:6: 6. FORM POST&]
[s5; If HTTP method is POST and content`-type field of header contains 
standard values (either `"application/x`-www`-form`-urlencoded`" 
or starts with `"multipart/`", Skylark parses the posted content 
and assigns posted values into shared variable space.&]
[s5; This makes handling FORM POSTs similar to GET with one exception: 
To avoid [^http`:`/`/en`.wikipedia`.org`/wiki`/Cross`-site`_request`_forgery^ CSRF] 
attacks, it is mandatory to include hidden field into dialog 
definition provided by function [@5 `$post`_identity()] `- Skylark 
manages everything required using session subsystem.&]
[s5; Request method is also part of handler path pattern (GET is 
default if not specified).&]
[s7; &]
[s7; #include <Skylark/Skylark.h>&]
[s7; &]
[s7; using namespace Upp;&]
[s7; &]
[s7; SKYLARK(HomePage, `"`")&]
[s7; `{&]
[s7; -|http.RenderResult(`"Skylark06/index`");&]
[s7; `}&]
[s7; &]
[s7; SKYLARK(Submit, `"submit:[* POST]`")&]
[s7; `{&]
[s7; -|http(`"RESULT`", ToUpper((String)http`[`"id`"`]))&]
[s7; -|-|.RenderResult(`"Skylark06/submit`");&]
[s7; `}&]
[s7; &]
[s7; struct MyApp : SkylarkApp `{&]
[s7; -|MyApp() `{&]
[s7; -|-|root `= `"myapp`";&]
[s7; -|#ifdef `_DEBUG&]
[s7; -|-|prefork `= 0;&]
[s7; -|-|use`_caching `= false;&]
[s7; -|#endif&]
[s7; -|`}&]
[s7; `};&]
[s7; &]
[s7; CONSOLE`_APP`_MAIN&]
[s7; `{&]
[s7; #ifdef `_DEBUG&]
[s7; -|StdLogSetup(LOG`_FILE`|LOG`_COUT);&]
[s7; -|Ini`::skylark`_log `= true;&]
[s7; #endif&]
[s7; &]
[s7; -|MyApp().Run();-|&]
[s7; `}&]
[s7; &]
[s5; [* Skylark06/index.witz:]&]
[s7; &]
[s7; <!DOCTYPE html>&]
[s7; <html>&]
[s7; <body>&]
[s7; <form action`=`$Submit method`=`"[* post]`" accept`-charset`=`"utf`-8`" 
enctype`=`"multipart/form`-data`">&]
[s7;    <P>&]
[s7;     [* `$post`_identity()]&]
[s7;     <INPUT type`=`"text`" name`=`"id`">&]
[s7;     <INPUT type`=`"submit`" value`=`"Submit`">&]
[s7;    </P>&]
[s7; </form>&]
[s7; </body>&]
[s7; </html>&]
[s7; &]
[s7; &]
[s5; [* Skylark06/submit.witz:]&]
[s7; &]
[s7; <!DOCTYPE html>&]
[s7; <html>&]
[s7; <body>&]
[s7; Result: `$RESULT<br>&]
[s7; <a href`=`$HomePage>Back to homepage</a>&]
[s7; </body>&]
[s7; </html>&]
[s7; &]
[s7; &]
[s5; Note: There also exists alternative POST`_RAW method marker in 
SKYLARK handler definition `- such handler also reacts to POST 
requests, but it avoids identity checks to prevent CSRF attacks.&]
[s5; &]
[s3;:7: 7. Session variables&]
[s5; Http`::SessioSet method can be used to store `'session variables`' 
that are persistent for specific browser across requests. Implementation 
is based on cookie, session variables are stored either in filesystem 
or in database (see Skylark configuration for details). Session 
variables are reflected in shared variable space (means its values 
are accessible using [* Http`::operator`[`]]) and are distinguished 
with `'.`' as the first character.&]
[s7; &]
[s7; #include <Skylark/Skylark.h>&]
[s7; &]
[s7; using namespace Upp;&]
[s7; &]
[s7; SKYLARK(HomePage, `"`")&]
[s7; `{&]
[s7; -|http.RenderResult(`"Skylark07/index`");&]
[s7; `}&]
[s7; &]
[s7; SKYLARK(Submit, `"submit:POST`")&]
[s7; `{&]
[s7; -|Value h `= [* http`[`".LIST`"`];]&]
[s7; -|ValueArray va;&]
[s7; -|if(IsValueArray(h))&]
[s7; -|-|va `= h;&]
[s7; -|va.Add(http`[`"id`"`]);&]
[s7; -|[* http.SessionSet(`".LIST`", va);]&]
[s7; -|http.Redirect(HomePage);&]
[s7; `}&]
[s7; &]
[s7; struct MyApp : SkylarkApp `{&]
[s7; -|MyApp() `{&]
[s7; -|-|root `= `"myapp`";&]
[s7; -|#ifdef `_DEBUG&]
[s7; -|-|prefork `= 0;&]
[s7; -|-|use`_caching `= false;&]
[s7; -|#endif&]
[s7; -|`}&]
[s7; `};&]
[s7; &]
[s7; CONSOLE`_APP`_MAIN&]
[s7; `{&]
[s7; #ifdef `_DEBUG&]
[s7; -|StdLogSetup(LOG`_FILE`|LOG`_COUT);&]
[s7; -|Ini`::skylark`_log `= true;&]
[s7; #endif&]
[s7; &]
[s7; -|MyApp().Run();-|&]
[s7; `}&]
[s7; &]
[s5; [* Skylark07/index.witz:]&]
[s7; &]
[s7; <!DOCTYPE html>&]
[s7; <html>&]
[s7; <body>&]
[s7; <form action`=`$Submit method`=`"post`" accept`-charset`=`"utf`-8`" 
enctype`=`"multipart/form`-data`">&]
[s7;    <P>&]
[s7;     `$post`_identity()&]
[s7;     <INPUT type`=`"text`" name`=`"id`">&]
[s7;     <INPUT type`=`"submit`" value`=`"Add to list`">&]
[s7;    </P>&]
[s7; </form>&]
[s7; List (`$count([* .LIST])):<br>&]
[s7; `$for(i in [* .LIST])&]
[s7; -|`"`$i`" &]
[s7; `$endfor&]
[s7; </body>&]
[s7; </html>&]
[s7; &]
[s5; &]
[s3;:8: 8. Ajax support&]
[s5; Skylark provides optional direct support for handling Ajax requests. 
On client side, this support is implemented using tiny JavaScript 
library `"skylark.js`".&]
[s7; &]
[s7; #include <Skylark/Skylark.h>&]
[s7; &]
[s7; using namespace Upp;&]
[s7; &]
[s7; SKYLARK(HomePage, `"`")&]
[s7; `{&]
[s7; -|http.RenderResult(`"Skylark08/index`");&]
[s7; `}&]
[s7; &]
[s7; SKYLARK([* Add], `"add:POST`")&]
[s7; `{&]
[s7; -|String r `= AsString(Nvl(http.Int(`"number1`")) `+ Nvl(http.Int(`"number2`")));
&]
[s7; [* -|http.Ux(`"result`", `"The result is: `" `+ r)]&]
[s7; [* -|    .UxSet(`"number1`", r);]&]
[s7; `}&]
[s7; &]
[s7; struct MyApp : SkylarkApp `{&]
[s7; -|MyApp() `{&]
[s7; -|-|root `= `"myapp`";&]
[s7; -|#ifdef `_DEBUG&]
[s7; -|-|prefork `= 0;&]
[s7; -|-|use`_caching `= false;&]
[s7; -|#endif&]
[s7; -|`}&]
[s7; `};&]
[s7; &]
[s7; CONSOLE`_APP`_MAIN&]
[s7; `{&]
[s7; #ifdef `_DEBUG&]
[s7; -|StdLogSetup(LOG`_FILE`|LOG`_COUT);&]
[s7; -|Ini`::skylark`_log `= true;&]
[s7; #endif&]
[s7; &]
[s7; -|MyApp().Run();-|&]
[s7; `}&]
[s7; &]
[s5; [* Skylark08/index.witz:]&]
[s7; &]
[s7; <!DOCTYPE html>&]
[s7; <html>&]
[s7; <script type`=`"text/javascript`" src`=`"[* `$static/Skylark/skylark.js]`"></scrip
t>&]
[s7; <body>&]
[s7; [* `$js`_identity()]&]
[s7; <div id`=`"[* numbers]`">&]
[s7;     <INPUT type`=`"text`" id`=`"[* number1]`">&]
[s7;     <INPUT type`=`"text`" id`=`"[* number2]`">&]
[s7;     <INPUT type`=`"button`" value`=`"Add`" onclick`=`'[* UxPost(`$Add, 
`"numbers`")]`'><br>&]
[s7; </div>&]
[s7; <div id`=`"result`"/>&]
[s7; </body>&]
[s7; </html>&]
[s7; &]
[s5; [*@5 `$static] variable is set by Skylark to the [@5 static`_dir 
]configuration parameter, if missing it is set to [/ root]/static, 
which makes Skylark to handle requests for static files (we expect 
that for production environment, serving static files will be 
off`-loaded to webserver). JavaScript function [*@5 UxPost ]recursively 
scans through html elements provided as second, third etc.. parameters 
and gathers all ids and values of input elements, packs them 
into POST format and sends to Skylark handler specified as first 
parameter. In this case it basically means that is sends [@5 number1] 
and [@5 number2] values to server handler [@5 Add]. Note the use 
of [*@5 `$js`_identity()] call `- this plays the same role in prevention 
of [^http`:`/`/en`.wikipedia`.org`/wiki`/Cross`-site`_request`_forgery^ CSRF] 
attacks as [@5 `$post`_identity] for FORM POSTs (alternative [*@5 UxGet] 
function uses GET requests and does not require [@5 `$js`_identity]). 
Also note the use of single quotes `' for onclick handler `- 
this is because links to handlers are expanded as double`-quoted 
strings.&]
[s5; The response to [@5 UxPost] or [@5 UxGet] requests is Skylark arbitrary 
format that can be used to directly alter current web page. [*@5 Ux] 
replaces innerHTML of matching (by id) element, [*@5 UxSet] sets 
the value attribute of matching element. Not shown here, [*@5 UxRender] 
is similar to Ux, but renders the text from witz template and 
finally [*@5 UxRun] can be used to run any JavaScript code in the 
client.&]
[s5; &]
[s3;:9: 9. Connecting SQL database&]
[s5; Skylark naturally uses U`+`+ SQL support when dealing with persistent 
storage, using `"session per`-thread`" mode. Because of this, 
database session needs to be connected when starting each thread 
`- this is done by overloading [@5 WorkThread] virtual method of 
SkylarkApp:&]
[s7; &]
[s7; #include <Skylark/Skylark.h>&]
[s7; #include <plugin/sqlite3/Sqlite3.h>&]
[s7; &]
[s7; using namespace Upp;&]
[s7; &]
[s7; #define  MODEL <Skylark09/myapp.sch>&]
[s7; #define  SCHEMADIALECT <plugin/sqlite3/Sqlite3Schema.h>&]
[s7; #include <Sql/sch`_header.h>&]
[s7; #include <Sql/sch`_schema.h>&]
[s7; #include <Sql/sch`_source.h>&]
[s7; &]
[s7; SKYLARK(HomePage, `"`")&]
[s7; `{&]
[s7; -|Sql sql;&]
[s7; -|sql `* Select(ID, NAME, LASTNAME)&]
[s7; -|      .From(PERSON)&]
[s7; -|      .OrderBy(LASTNAME, NAME);&]
[s7; -|ValueArray person;&]
[s7; -|ValueMap vm;&]
[s7; -|while(sql.Fetch(vm))&]
[s7; -|-|person.Add(vm);&]
[s7; -|http(`"PERSON`", person)&]
[s7; -|    .RenderResult(`"Skylark09/index`");&]
[s7; `}&]
[s7; &]
[s7; struct MyApp : SkylarkApp `{&]
[s7; -|[* virtual void WorkThread();]&]
[s7; &]
[s7; -|MyApp() `{&]
[s7; -|-|root `= `"myapp`";&]
[s7; -|-|threads `= 1; // Sqlite3 does not like threads...&]
[s7; -|#ifdef `_DEBUG&]
[s7; -|-|prefork `= 0;&]
[s7; -|-|use`_caching `= false;&]
[s7; -|#endif&]
[s7; -|`}&]
[s7; `};&]
[s7; &]
[s7; void InitModel()&]
[s7; `{&]
[s7; #ifdef `_DEBUG&]
[s7; -|SqlSchema sch(SQLITE3);&]
[s7; -|All`_Tables(sch);&]
[s7; -|SqlPerformScript(sch.Upgrade());&]
[s7; -|SqlPerformScript(sch.Attributes());&]
[s7; -|sch.SaveNormal();&]
[s7; #endif&]
[s7; `}&]
[s7; &]
[s7; void OpenSQL(Sqlite3Session`& sqlite3)&]
[s7; `{&]
[s7; -|if(!sqlite3.Open(ConfigFile(`"db`"))) `{&]
[s7; -|-|LOG(`"Can`'t create or open database file`\n`");&]
[s7; -|-|Exit(1);&]
[s7; -|`}&]
[s7; #ifdef `_DEBUG&]
[s7; -|sqlite3.LogErrors();&]
[s7; -|sqlite3.SetTrace();&]
[s7; #endif&]
[s7; -|SQL `= sqlite3;&]
[s7; `}&]
[s7; &]
[s7; [* void MyApp`::WorkThread()]&]
[s7; [* `{]&]
[s7; [* -|Sqlite3Session sqlite3;]&]
[s7; [* -|OpenSQL(sqlite3);]&]
[s7; [* -|RunThread();]&]
[s7; [* `}]&]
[s7; &]
[s7; void InitDB()&]
[s7; `{&]
[s7; -|Sqlite3Session sqlsession;&]
[s7; -|OpenSQL(sqlsession);&]
[s7; -|SqlSchema sch(SQLITE3);&]
[s7; -|All`_Tables(sch);&]
[s7; -|SqlPerformScript(sch.Upgrade());&]
[s7; -|SqlPerformScript(sch.Attributes());&]
[s7; &]
[s7; -|SQL `* Insert(PERSON)(NAME,`"Joe`")(LASTNAME,`"Smith`");&]
[s7; -|SQL `* Insert(PERSON)(NAME,`"Mike`")(LASTNAME,`"Carpenter`");&]
[s7; -|SQL `* Insert(PERSON)(NAME,`"Jon`")(LASTNAME,`"Goober`");&]
[s7; `}&]
[s7; &]
[s7; CONSOLE`_APP`_MAIN&]
[s7; `{&]
[s7; #ifdef `_DEBUG&]
[s7; -|StdLogSetup(LOG`_FILE`|LOG`_COUT);&]
[s7; -|Ini`::skylark`_log `= true;&]
[s7; #endif&]
[s7; &]
[s7; -|DeleteFile(ConfigFile(`"db`")); // for this example, always 
create a new DB&]
[s7; -|InitDB();&]
[s7; &]
[s7; -|MyApp().Run();-|&]
[s7; `}&]
[s7; &]
[s5; [* Skylark09/index.witz:]&]
[s7; &]
[s7; <!DOCTYPE html>&]
[s7; <html>&]
[s7; <body>&]
[s7; <table border`=`"1`">&]
[s7; <tr>&]
[s7;   <th>No.</th>&]
[s7;   <th>First Name</th>&]
[s7;   <th>Last Name</th>&]
[s7; </tr>&]
[s7; `$for(i in PERSON)&]
[s7; -|<tr>&]
[s7; -|  <td>`$i.`_index.</td>&]
[s7; -|  <td>`$i.NAME</td>&]
[s7; -|  <td>`$i.LASTNAME</td>&]
[s7; -|</tr>-|&]
[s7; `$/&]
[s7; </table>&]
[s7; </body>&]
[s7; </html>&]
[s7; &]
[s5; [* Skylark09/myapp.sch:]&]
[s7; &]
[s7; TABLE`_(PERSON)&]
[s7; -|INT`_    (ID)      PRIMARY`_KEY AUTO`_INCREMENT&]
[s7; -|STRING`_ (NAME, 200)&]
[s7; -|STRING`_ (LASTNAME, 200)&]
[s7; END`_TABLE&]
[s7; &]
[s5; &]
[s3;:10: 10. Advanced SQL&]
[s5; Http class contains some advanced convenience support for dealing 
with SQL databases:&]
[s5;l160;i150;O0; It is possible to fill result set of SqlSelect 
into witz variable as demonstrated by [@5 HomePage ]handler&]
[s5;l160;i150;O0; Http`::Insert inserts a row to database, reading 
values of columns based on known (from .sch file) names of columns 
from equally named variables of shared variable space (which 
come from POST or GET request), as demonstrated by [@5 SubmitNew].&]
[s5;l160;i150;O0; Http`::Update updates a row in database, again based 
on names of columns and shared variable space, as demonstrated 
by [@5 SubmitEdit].&]
[s5;l160;i150;O0; It is also possible to add shared variables based 
on single row select, names being then same as names of columns, 
as demonstrated by [@5 Edit].&]
[s5; &]
[s7; &]
[s7; #include <Skylark/Skylark.h>&]
[s7; #include <plugin/sqlite3/Sqlite3.h>&]
[s7; &]
[s7; using namespace Upp;&]
[s7; &]
[s7; #define  MODEL <Skylark09/myapp.sch>&]
[s7; #define  SCHEMADIALECT <plugin/sqlite3/Sqlite3Schema.h>&]
[s7; #include <Sql/sch`_header.h>&]
[s7; #include <Sql/sch`_schema.h>&]
[s7; #include <Sql/sch`_source.h>&]
[s7; &]
[s7; SKYLARK(HomePage, `"`")&]
[s7; `{&]
[s7; /`*&]
[s7; -|Sql sql;&]
[s7; -|sql `* Select(ID, NAME, LASTNAME)&]
[s7; -|      .From(PERSON)&]
[s7; -|      .OrderBy(LASTNAME, NAME);&]
[s7; -|ValueArray person;&]
[s7; -|ValueMap vm;&]
[s7; -|while(sql.Fetch(vm))&]
[s7; -|-|person.Add(vm);&]
[s7; `*/&]
[s7; -|[* http(`"PERSON`", Select(SqlAll()).From(PERSON).OrderBy(LASTNAME, 
NAME))]&]
[s7; -|.RenderResult(`"Skylark10/index`");&]
[s7; `}&]
[s7; &]
[s7; SKYLARK(SubmitNew, `"create/submit:POST`")&]
[s7; `{&]
[s7; /`*&]
[s7; -|SQL `* Insert(PERSON)(NAME, http`[`"name`"`])(LASTNAME, http`[`"lastname`"`]);&]
[s7; `*/&]
[s7; -|[* SQL `* http.Insert(PERSON);]&]
[s7; -|http.Redirect(HomePage);&]
[s7; `}&]
[s7; &]
[s7; SKYLARK(New, `"create`")&]
[s7; `{&]
[s7; -|http(`"ACTION`", SubmitNew)&]
[s7; -|.RenderResult(`"Skylark10/Dialog`");&]
[s7; `}&]
[s7; &]
[s7; SKYLARK(SubmitEdit, `"edit/submit/`*:POST`")&]
[s7; `{&]
[s7; /`*&]
[s7; -|SQL `* Update(PERSON)&]
[s7; -|-|-|(NAME, http`[`"name`"`])&]
[s7; -|-|-|(LASTNAME, http`[`"lastname`"`])&]
[s7; -|-|-|.Where(ID `=`= http.Int(0));&]
[s7; -|;&]
[s7; `*/&]
[s7; -|[* SQL `* http.Update(PERSON).Where(ID `=`= http.Int(0));]&]
[s7; -|http.Redirect(HomePage);&]
[s7; `}&]
[s7; &]
[s7; SKYLARK(Edit, `"edit/`*`")&]
[s7; `{&]
[s7; -|int id `= http.Int(0);&]
[s7; /`*&]
[s7; -|Sql sql;&]
[s7; -|sql `* Select(NAME, LASTNAME).From(PERSON).Where(ID `=`= id);&]
[s7; -|if(!sql.Fetch()) `{&]
[s7; -|-|http.Redirect(HomePage);&]
[s7; -|-|return;&]
[s7; -|`}&]
[s7; -|http(`"NAME`", sql`[NAME`])(`"LASTNAME`", sql`[LASTNAME`]);&]
[s7; `*/&]
[s7; -|[* http]&]
[s7; [* -|-|(Select(SqlAll()).From(PERSON).Where(ID `=`= id))]&]
[s7; -|-|(`"ID`", id)&]
[s7; -|-|(`"ACTION`", SubmitEdit, id)&]
[s7; -|.RenderResult(`"Skylark10/Dialog`");&]
[s7; `}&]
[s7; &]
[s7; struct MyApp : SkylarkApp `{&]
[s7; -|virtual void WorkThread();&]
[s7; &]
[s7; -|MyApp() `{&]
[s7; -|-|root `= `"myapp`";&]
[s7; -|-|threads `= 1; // Sqlite3 does not like threads...&]
[s7; -|#ifdef `_DEBUG&]
[s7; -|-|prefork `= 0;&]
[s7; -|-|use`_caching `= false;&]
[s7; -|#endif&]
[s7; -|`}&]
[s7; `};&]
[s7; &]
[s7; void InitModel()&]
[s7; `{&]
[s7; #ifdef `_DEBUG&]
[s7; -|SqlSchema sch(SQLITE3);&]
[s7; -|All`_Tables(sch);&]
[s7; -|SqlPerformScript(sch.Upgrade());&]
[s7; -|SqlPerformScript(sch.Attributes());&]
[s7; -|sch.SaveNormal();&]
[s7; #endif&]
[s7; `}&]
[s7; &]
[s7; void OpenSQL(Sqlite3Session`& sqlite3)&]
[s7; `{&]
[s7; -|if(!sqlite3.Open(ConfigFile(`"db`"))) `{&]
[s7; -|-|LOG(`"Can`'t create or open database file`\n`");&]
[s7; -|-|Exit(1);&]
[s7; -|`}&]
[s7; #ifdef `_DEBUG&]
[s7; -|sqlite3.LogErrors();&]
[s7; -|sqlite3.SetTrace();&]
[s7; #endif&]
[s7; -|SQL `= sqlite3;&]
[s7; `}&]
[s7; &]
[s7; void MyApp`::WorkThread()&]
[s7; `{&]
[s7; -|Sqlite3Session sqlite3;&]
[s7; -|OpenSQL(sqlite3);&]
[s7; -|RunThread();&]
[s7; `}&]
[s7; &]
[s7; void InitDB()&]
[s7; `{&]
[s7; -|Sqlite3Session sqlsession;&]
[s7; -|OpenSQL(sqlsession);&]
[s7; -|SqlSchema sch(SQLITE3);&]
[s7; -|All`_Tables(sch);&]
[s7; -|SqlPerformScript(sch.Upgrade());&]
[s7; -|SqlPerformScript(sch.Attributes());&]
[s7; `}&]
[s7; &]
[s7; CONSOLE`_APP`_MAIN&]
[s7; `{&]
[s7; #ifdef `_DEBUG&]
[s7; -|StdLogSetup(LOG`_FILE`|LOG`_COUT);&]
[s7; -|Ini`::skylark`_log `= true;&]
[s7; #endif&]
[s7; &]
[s7; -|InitDB();&]
[s7; &]
[s7; -|MyApp().Run();-|&]
[s7; `}&]
[s7; &]
[s5; [* Skylark10/index.witz:]&]
[s7; &]
[s7; <!DOCTYPE html>&]
[s7; <html>&]
[s7; <body>&]
[s7; <table border`=`"1`">&]
[s7; <tr>&]
[s7;   <th>No.</th>&]
[s7;   <th>First Name</th>&]
[s7;   <th>Last Name</th>&]
[s7; </tr>&]
[s7; `$for(i in PERSON)&]
[s7; -|<tr>&]
[s7; -|  <td>`$(i.`_index `+ 1).</td>&]
[s7; -|  <td>`$i.NAME</td>&]
[s7; -|  <td>`$i.LASTNAME</td>&]
[s7; -|  <td><a href`=`$Edit(i.ID)>Edit</a></td>&]
[s7; -|</tr>-|&]
[s7; `$/&]
[s7; </table>&]
[s7; <a href`=`$New>Create new</a>&]
[s7; </body>&]
[s7; </html>&]
[s7; &]
[s5; [* Skylark10/dialog.witz:]&]
[s7; &]
[s7; <!DOCTYPE html>&]
[s7; <html>&]
[s7; <body>&]
[s7; <FORM action`=`$ACTION method`=`"post`" accept`-charset`=`"utf`-8`" 
enctype`=`"multipart/form`-data`">&]
[s7; `$post`_identity()&]
[s7; <P>&]
[s7;     First name: <INPUT type`=`"text`" name`=`"name`" value`=`"`$NAME`"><BR>&]
[s7;     Last name: <INPUT type`=`"text`" name`=`"lastname`" value`=`"`$LASTNAME`"><BR
>&]
[s7;     <INPUT type`=`"submit`" value`=`"Send`" name`=`"OK`"/><BR>&]
[s7; </P>&]
[s7; </FORM>&]
[s7; </table>&]
[s7; </body>&]
[s7; </html>&]
[s7; &]
[s5; [* Skylark10/myapp.sch:]&]
[s7; &]
[s7; TABLE`_(PERSON)&]
[s7; -|INT`_    (ID)      PRIMARY`_KEY AUTO`_INCREMENT&]
[s7; -|STRING`_ (NAME, 200)&]
[s7; -|STRING`_ (LASTNAME, 200)&]
[s7; END`_TABLE&]
[s7; &]
[s5; &]
[s3;:11: 11. Language support&]
[s5; Skylark language support is based on session variables:&]
[s5; `"[@5 .`_`_lang`_`_]`" contains integer with U`+`+ language identifier&]
[s5; `"[@5 .language]`" contains the string form of this identifier 
(e.g. `"cs`-cz`")&]
[s5; [@5 Http`::SetLanguage ]method sets both variables and also SetLanguage 
(U`+`+ Core function to switch U`+`+ language). When loading 
.witz templates, Skylark first searches for templates for specific 
language `- language can be a part of template name, e.g. [%-*@5 index.][%-*_@5 cs`-c
z][%-*@5 .witz], only if not found, `'generic`' version (like  
[%-*@5 index.witz]) is used. Also, after loading the session, U`+`+ 
Core SetLanguage is invoked with current `".`_`_lang`_`_`" setting, 
that way U`+`+ i18n system can be used in Skylark handlers.&]
[s7; &]
[s7; #include <Skylark/Skylark.h>&]
[s7; #include <plugin/sqlite3/Sqlite3.h>&]
[s7; &]
[s7; using namespace Upp;&]
[s7; &]
[s7; SKYLARK(HomePage, `"`")&]
[s7; `{&]
[s7; -|http(`"VAR`", [* t`_(`"Aborted by user.`")])&]
[s7; -|    .RenderResult(`"Skylark11/index`");&]
[s7; `}&]
[s7; &]
[s7; SKYLARK([* SetLanguage], `"setlanguage/`*`")&]
[s7; `{&]
[s7; -|int lang `= LNGFromText(http`[0`]);&]
[s7; -|if(lang)&]
[s7; -|-|[* http.SetLanguage(lang);]&]
[s7; -|http.Redirect(HomePage);&]
[s7; `}&]
[s7; &]
[s7; struct MyApp : SkylarkApp `{&]
[s7; -|MyApp() `{&]
[s7; -|-|root `= `"myapp`";&]
[s7; -|-|threads `= 1; // Sqlite3 does not like threads...&]
[s7; -|#ifdef `_DEBUG&]
[s7; -|-|prefork `= 0;&]
[s7; -|-|use`_caching `= false;&]
[s7; -|#endif&]
[s7; -|`}&]
[s7; `};&]
[s7; &]
[s7; CONSOLE`_APP`_MAIN&]
[s7; `{&]
[s7; #ifdef `_DEBUG&]
[s7; -|StdLogSetup(LOG`_FILE`|LOG`_COUT);&]
[s7; -|Ini`::skylark`_log `= true;&]
[s7; #endif&]
[s7; -|MyApp().Run();-|&]
[s7; `}&]
[s7; &]
[s5; [* Skylark11/lang.witz:]&]
[s7; &]
[s7; <a href`=`$[* SetLanguage](`"en`-us`")>EN</a>&]
[s7; <a href`=`$[* SetLanguage](`"cs`-cz`")>CZ</a>&]
[s7; <br>&]
[s7; Current language: [* `$.language]<br>&]
[s7; &]
[s5; [* Skylark11/index.witz:]&]
[s7; &]
[s7; <!DOCTYPE html>&]
[s7; <html>&]
[s7; <body>&]
[s7; #include lang&]
[s7; English version<br>&]
[s7; Variable value: `$VAR&]
[s7; </body>&]
[s7; </html>&]
[s7; &]
[s5;%- [* Skylark11/index.][*_ cs`-cz][* .witz:]&]
[s7; &]
[s7; <!DOCTYPE html>&]
[s7; <html>&]
[s7; <body>&]
[s7; #include lang&]
[s7; Česká verze<br>&]
[s7; Hodnota proměnné: `$VAR&]
[s7; </body>&]
[s7; </html>&]
[s7; &]
[s5; &]
[s3;:12: 12. Packs&]
[s5; Sometimes it is useful to parametrize a group of handlers so 
that they can be used in different contexts. For example, the 
Create/Edit/Delete operations in chapter 10 share many elements 
(e.g. table name or dialog) and by parametrizing them, it would 
be possible to use them with different table. Such thing is possible 
by creating `"pack`" class. Such class has to be derived from 
[@5 SkylarkPack ]base class, must have [@5 CLASSNAME ]typedef and 
must have [@5 Use ]method.&]
[s5; Pack handlers are normal methods of such class and are registred 
in [@5 Use ]method by [@5 SKYLARK`_METHOD ]macro. To reference other 
method of the same class (e.g. for Redirect or as witz parameter), 
use [@5 THISLINK ]macro.&]
[s5; The instance of pack is created with [@5 SKYLARK`_USE]. This effectively 
creates a global variable of pack class type and register handlers 
for this instance, combining variable name and method name as 
name of handler and provided urls to get the handler url. [@5 SKYLARK`_USE 
]has `"body`" that gets executed during registration phase and 
can be used to setup parameters of pack instance.&]
[s5; Url links to pack methods are then expressed as [/@5 instance:method][@5  
]in witz templates and as LINK(instance, method) in C`+`+ code.&]
[s5; Note also that HandlerId is a special simple type able to store 
either [@5 LINK ]or [@5 THISLINK ]originated reference to pack method 
or pointer to handler function.&]
[s7; .....&]
[s7; &]
[s7; struct CreateEditDelete : [* SkylarkPack ]`{&]
[s7; -|[* HandlerId   ]back;&]
[s7; -|SqlId       table;&]
[s7; -|SqlId       key;&]
[s7; -|SqlSet      columns;&]
[s7; -|String      dialog;&]
[s7; &]
[s7; -|void Create(Http`& http);&]
[s7; -|void SubmitCreate(Http`& http);&]
[s7; -|void Edit(Http`& http);&]
[s7; -|void SubmitEdit(Http`& http);&]
[s7; -|void Delete(Http`& http);&]
[s7; &]
[s7; -|typedef CreateEditDelete CLASSNAME;&]
[s7; &]
[s7; -|void Use();&]
[s7; -|&]
[s7; -|CreateEditDelete() `{ key `= SqlId(`"ID`"); columns `= SqlSet(SqlAll()); 
`}&]
[s7; `};&]
[s7; &]
[s5; [* Skylark12/Cud.cpp:]&]
[s7; &]
[s7; #include `"Skylark12.h`"&]
[s7; &]
[s7; void CreateEditDelete`::Create(Http`& http)&]
[s7; `{&]
[s7; -|http(`"ACTION`", [* THISLINK](SubmitCreate))&]
[s7; -|.RenderResult(dialog);&]
[s7; `}&]
[s7; &]
[s7; void CreateEditDelete`::SubmitCreate(Http`& http)&]
[s7; `{&]
[s7; -|SQL `* http.Insert(table);&]
[s7; -|http.Redirect(back);&]
[s7; `}&]
[s7; &]
[s7; void CreateEditDelete`::Edit(Http`& http)&]
[s7; `{&]
[s7; -|int id `= http.Int(0);&]
[s7; -|http&]
[s7; -|-|(Select(columns).From(table).Where(key `=`= id))&]
[s7; -|-|(`"ID`", id)&]
[s7; -|-|(`"ACTION`", [* THISLINK](SubmitEdit), id)&]
[s7; -|.RenderResult(dialog);&]
[s7; `}&]
[s7; &]
[s7; void CreateEditDelete`::SubmitEdit(Http`& http)&]
[s7; `{&]
[s7; -|SQL `* http.Update(table).Where(key `=`= http.Int(0));&]
[s7; -|http.Redirect(back);&]
[s7; `}&]
[s7; &]
[s7; void CreateEditDelete`::Delete(Http`& http)&]
[s7; `{&]
[s7; -|SQL `* SqlDelete(table).Where(key `=`= atoi(http`[0`]));&]
[s7; -|http.Redirect(back);&]
[s7; `}&]
[s7; &]
[s7; void CreateEditDelete`::[* Use]()&]
[s7; `{&]
[s7; -|[* SKYLARK`_METHOD](Create, `"create`");&]
[s7; -|[* SKYLARK`_METHOD](SubmitCreate, `"create`_submit:POST`");&]
[s7; -|[* SKYLARK`_METHOD](Edit, `"edit/`*`");&]
[s7; -|[* SKYLARK`_METHOD](SubmitEdit, `"submit`_edit/`*:POST`");&]
[s7; -|[* SKYLARK`_METHOD](Delete, `"delete/`*`");&]
[s7; `}&]
[s7; &]
[s5; [* Skylark12/Handlers.icpp:]&]
[s7; &]
[s7; #include `"Skylark12.h`"&]
[s7; &]
[s7; void HomePage(Http`&);&]
[s7; &]
[s7; [* SKYLARK`_USE](CreateEditDelete, Person, `"person`")&]
[s7; `{&]
[s7; -|Person.back `= HomePage;&]
[s7; -|Person.table `= PERSON;&]
[s7; -|Person.dialog `= `"Skylark12/dialog`";&]
[s7; `}&]
[s7; &]
[s7; SKYLARK(HomePage, `"`")&]
[s7; `{&]
[s7; -|http(`"PERSON`", Select(ID, FIRSTNAME, LASTNAME, EMAIL).From(PERSON)&]
[s7; -|               .OrderBy(LASTNAME, FIRSTNAME))&]
[s7; -|(`"CREATE`", [* LINK](Person, Create))&]
[s7; -|.RenderResult(`"Skylark12/index`");&]
[s7; `}&]
[s7; &]
[s7; SKYLARK(CatchAll, `"`*`*`")&]
[s7; `{&]
[s7; -|http.Redirect(HomePage);&]
[s7; `}&]
[s7; &]
[s5; [* Skylark12/index.witz:]&]
[s7; &]
[s7; #include Skylark/Base&]
[s7; &]
[s7; #define BODY&]
[s7; &]
[s7; <table border`=`"1`" id`=`"persons`">&]
[s7; <tr>&]
[s7;   <th>First Name</th>&]
[s7;   <th>Last Name</th>&]
[s7;   <th>Email</th>&]
[s7; </tr>&]
[s7; `$for(i in PERSON)&]
[s7; -|<tr>&]
[s7; -|  <td>`$i.FIRSTNAME</td>&]
[s7; -|  <td>`$i.LASTNAME</td>&]
[s7; -|  <td>`$i.EMAIL</td>&]
[s7; -|  <td>&]
[s7; -|  -|<a href`=`$[* Person:Edit](i.ID)>Edit</a>&]
[s7; -|  -|<a href`=`$[* Person:Delete](i.ID)>Delete</a>&]
[s7; -|  </td>&]
[s7; -|</tr>-|&]
[s7; `$/&]
[s7; </table>&]
[s7; &]
[s7; <p/>&]
[s7; <a href`=`$[* Person:Create]>Insert new person</a>&]
[s7; <a href`=`$[* CREATE]>Insert new person using LINK</a>&]
[s7; &]
[s5; &]
[s3; Recommended tutorials:&]
[s5; If you want to learn more, we have several tutorials that you 
can find useful:&]
[s5;l160;i150;O0; [^topic`:`/`/Sql`/srcdoc`/tutorial`$en`-us^ SQL tutorial] 
`- everything you should know to work efficiency with databases 
within U`+`+ framework.]]