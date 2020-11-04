/*!
  \page GFSD FastScript Documentation

  ---everything below this is in HTML an created using https://wordtohtml.net---

<h1 style="text-align: center;"><span style='font-family: "Lucida Console", Monaco, monospace;'>This is the bad documentation of the Gamanius&apos; Fast Script</span></h1>
<p><span style="font-family: 'Lucida Console', Monaco, monospace;"><br></span></p>
<p><span style="font-family: 'Lucida Console', Monaco, monospace;">The symbol &apos;<strong>#</strong>&apos; marks a comment. Everything after this symbol will be ignored by the Tokenizer till the end of line</span></p>
<blockquote>
	<p><span style='font-family: "Lucida Console", Monaco, monospace; color: rgb(255, 0, 0);'>*some function* #This is a comment</span></p>
</blockquote>
<hr>
<p><span style="font-family: 'Lucida Console', Monaco, monospace;">The character set <strong>&quot;-#-&quot;</strong> marks the start and end of a comment block. Everything in between will be ignored by the Tokenizer</span></p>
<blockquote>
	<p><span style='font-family: "Lucida Console", Monaco, monospace; color: rgb(255, 0, 0);'>-#-</span></p>
	<p><span style="color: rgb(255, 0, 0);"><span style="font-family: 'Lucida Console', Monaco, monospace;">this is a comment</span></span></p>
	<p><span style='font-family: "Lucida Console", Monaco, monospace; color: rgb(255, 0, 0);'>-#-</span></p>
</blockquote>
<hr>
<h2><span style="font-family: 'Lucida Console', Monaco, monospace;">Identifier and Functions:</span></h2>
<p><span style="font-family: 'Lucida Console', Monaco, monospace;"><strong><em>num Identifier = numeric-value</em></strong></span></p>
<p><span style="font-family: 'Lucida Console', Monaco, monospace;">Used to declare a new variable. This variable hold a 64bit floating point value and will be alive till the end of the Interpreter instance</span></p>
<blockquote>
	<p><span style='font-family: "Lucida Console", Monaco, monospace; color: rgb(255, 0, 0);'>num ThisIsAVariable 1234</span></p>
	<p><span style='font-family: "Lucida Console", Monaco, monospace; color: rgb(255, 0, 0);'>print ThisIsAVariable #will print &quot;1234&quot;</span></p>
</blockquote>
<p><br></p>
<p><em><span style="font-family: 'Lucida Console', Monaco, monospace;"><strong>string Identifier = string-value</strong></span></em></p>
<p><span style="font-family: 'Lucida Console', Monaco, monospace;">Used to declare a new variable. This variable holds a char buffer that is interpreted as a string. A string is declared by using the &apos;&quot;&apos; symbol.</span></p>
<blockquote>
	<p><span style='font-family: "Lucida Console", Monaco, monospace; color: rgb(255, 0, 0);'>string TestString <strong>&quot;</strong>test<strong>&quot;</strong></span></p>
	<p><span style='font-family: "Lucida Console", Monaco, monospace; color: rgb(255, 0, 0);'>print TestString #will print &quot;test&quot;</span></p>
</blockquote>
<p><br></p>
<p><span style="font-family: 'Lucida Console', Monaco, monospace;"><strong><em>numarray identifier&nbsp;</em></strong><em>=</em><strong><em>&nbsp;value1 value2 ... value-x</em></strong></span></p>
<p><span style="font-family: 'Lucida Console', Monaco, monospace;">Used to declare a new variable. Instead of holding just one 64bit floating point value, this can hold up multiple values.</span></p>
<blockquote>
	<p><span style='font-family: "Lucida Console", Monaco, monospace; color: rgb(255, 0, 0);'>numarray TestArray = 1 2 3 4 5 6 7 8 9 10</span></p>
	<p><span style='font-family: "Lucida Console", Monaco, monospace; color: rgb(255, 0, 0);'>print TestArray #will print &quot;1.000000, 2.000000, 3.000000, 4.000000, 5.000000, 6.000000, 7.000000, 8.000000, 9.000000, 10.000000&quot;</span></p>
</blockquote>
<p><br></p>
<p><span style="font-family: 'Lucida Console', Monaco, monospace;"><strong><em>stringarray identifier&nbsp;</em></strong><em>=</em><strong><em>&nbsp;value1 value2 ... value-x</em></strong></span></p>
<p><span style="font-family: 'Lucida Console', Monaco, monospace;">Used to declare a new variable. This variable hold multiple string variables.</span></p>
<blockquote>
	<p><span style='font-family: "Lucida Console", Monaco, monospace; color: rgb(255, 0, 0);'>stringarray TestArray = &quot;hello&quot; &quot;how are you?&quot;</span></p>
	<p><span style='font-family: "Lucida Console", Monaco, monospace; color: rgb(255, 0, 0);'>print TestArray #will print &quot;hello, how are you?&quot;</span></p>
</blockquote>
<p><br></p>
<p><span style="font-family: 'Lucida Console', Monaco, monospace;"><em><strong>print</strong></em><strong>&nbsp;<em>data</em></strong><strong>(Number, String, Number variable, String variable, Number array variable, String array variable)</strong></span></p>
<p><span style="font-family: 'Lucida Console', Monaco, monospace;">The print function can be used to print out most of the data types defined in this scripting language</span></p>
<blockquote>
	<p><span style='font-family: "Lucida Console", Monaco, monospace; color: rgb(255, 0, 0);'>print &quot;Hello world&quot;</span></p>
</blockquote>
<p><br></p>
<p><span style="font-family: 'Lucida Console', Monaco, monospace;"><strong><em>addarray&nbsp;</em><em>array</em>(number array variable, string array variable)<em>&nbsp;value</em>(number variable, string variable, numeric-value, string-value)</strong></span></p>
<p><span style="font-family: 'Lucida Console', Monaco, monospace;">Will add a new element into an existing array. The type of which array the arrays stores must be the same as the type that will be added to the array. Otherwise, the behaviour is undefined.</span></p>
<blockquote>
	<p><span style='font-family: "Lucida Console", Monaco, monospace; color: rgb(255, 0, 0);'>numarray TestArray = 1 2 3</span></p>
	<p><span style="color: rgb(255, 0, 0);"><span style="font-family: 'Lucida Console', Monaco, monospace;">addarray TestArray 4</span></span></p>
	<p><span style="color: rgb(255, 0, 0);"><span style='font-family: "Lucida Console", Monaco, monospace;'>print TestArray #will print out &quot;1.000000, 2.000000, 3.000000, 4.000000&quot;</span></span></p>
</blockquote>
<p><br></p>
<p><span style="font-family: 'Lucida Console', Monaco, monospace;"><strong><em>sizearray array</em>(number array variable, string array variable)<em>&nbsp;num</em>(number variable)</strong></span></p>
<p><span style="font-family: 'Lucida Console', Monaco, monospace;">Will save the size of the array into the number variable.</span></p>
<blockquote>
	<p><span style='font-family: "Lucida Console", Monaco, monospace; color: rgb(255, 0, 0);'>numarray TestArray = 1 2 3</span></p>
	<p><span style="color: rgb(255, 0, 0);"><span style="font-family: 'Lucida Console', Monaco, monospace;">num Size = 0</span></span></p>
	<p><span style="color: rgb(255, 0, 0);"><span style="font-family: 'Lucida Console', Monaco, monospace;">sizearray TestArray Size</span></span></p>
	<p><span style='font-family: "Lucida Console", Monaco, monospace; color: rgb(255, 0, 0);'>print Size #will print out &quot;3.000000&quot;</span></p>
</blockquote>
<p><br></p>
<p><span style="font-family: 'Lucida Console', Monaco, monospace;"><strong><em>setarray array</em>(number array variable, string array variable)<em>&nbsp;index</em>(number variable, numeric-value)<em>&nbsp;data</em>(number variable, string variable, numeric-value, string-value)<em>&nbsp;</em></strong></span></p>
<p><span style="font-family: 'Lucida Console', Monaco, monospace;">With this function, one can change the value of a given index in a array. The type of which array the arrays stores must be the same as the type that will be added to the array. Otherwise, the behaviour is undefined. If the data is a variable, the value will be copied.&nbsp;</span></p>
<blockquote>
	<p><span style='font-family: "Lucida Console", Monaco, monospace; color: rgb(255, 0, 0);'>numarray TestArray = 1 2 3</span></p>
	<p><span style="color: rgb(255, 0, 0);"><span style="font-family: 'Lucida Console', Monaco, monospace;">num Important = 0</span></span></p>
	<p><span style="color: rgb(255, 0, 0);"><span style="font-family: 'Lucida Console', Monaco, monospace;">setarray TestArray 2 Important</span></span></p>
	<p><span style='font-family: "Lucida Console", Monaco, monospace; color: rgb(255, 0, 0);'>print TestArray #will print &quot;1.000000, 2.000000, 0.000000&quot;</span></p>
</blockquote>
<p><br></p>
<p><span style="font-family: 'Lucida Console', Monaco, monospace;"><strong><em>getarray&nbsp;</em><em>array</em>(number array variable, string array variable)<em>&nbsp;index</em>(number variable, numeric-value)<em>&nbsp;data</em>(number variable, string variable) &nbsp;</strong></span></p>
<p><span style="font-family: 'Lucida Console', Monaco, monospace;">Will retrieve the value at the given index and copy it into the data variable</span></p>
<blockquote>
	<p><span style='font-family: "Lucida Console", Monaco, monospace; color: rgb(255, 0, 0);'>numarray TestArray = 1 2 3</span></p>
	<p><span style="color: rgb(255, 0, 0);"><span style="font-family: 'Lucida Console', Monaco, monospace;">num Important = 0</span></span></p>
	<p><span style="color: rgb(255, 0, 0);"><span style="font-family: 'Lucida Console', Monaco, monospace;">getarray TestArray 2 Important</span></span></p>
	<p><span style='font-family: "Lucida Console", Monaco, monospace; color: rgb(255, 0, 0);'>print Important #will print &quot;3.000000&quot;</span></p>
</blockquote>
<hr>
<h2><span style="font-family: 'Lucida Console', Monaco, monospace;">Operations:</span></h2>
<p><span style="font-family: 'Lucida Console', Monaco, monospace;"><strong><em>identifier (+, -, *, /) (identifier, number)</em></strong></span></p>
<p><span style="font-family: 'Lucida Console', Monaco, monospace;">This will add/subtract/multiply/divide the identifier value with the other value. The identifier will be then overridden with the calculated value&nbsp;</span></p>
<blockquote>
	<p><span style='font-family: "Lucida Console", Monaco, monospace; color: rgb(255, 0, 0);'>num value = 1</span></p>
	<p><span style="color: rgb(255, 0, 0);"><span style="font-family: 'Lucida Console', Monaco, monospace;">num othervalue = 2</span></span></p>
	<p><span style="color: rgb(255, 0, 0);"><span style="font-family: 'Lucida Console', Monaco, monospace;">value + othervalue</span></span></p>
	<p><span style="color: rgb(255, 0, 0);"><span style="font-family: 'Lucida Console', Monaco, monospace;">print value #will print &quot;3.000000&quot;</span></span></p>
	<p><span style="color: rgb(255, 0, 0);"><span style="font-family: 'Lucida Console', Monaco, monospace;">value - othervalue</span></span></p>
	<p><span style='font-family: "Lucida Console", Monaco, monospace; color: rgb(255, 0, 0);'>print value #will print &quot;1.000000&quot;</span></p>
</blockquote>
<div id="gtx-anchor" style="position: absolute; visibility: hidden; left: 10px; top: 1395px; width: 1161px; height: 186px;"><br></div>
<div class="jfk-bubble gtx-bubble" style="visibility: visible; left: 11px; top: 1177px; opacity: 1;">
	<div class="jfk-bubble-content-id" id="bubble-28">
		<div id="gtx-host" style="min-width: 200px; max-width: 400px;"><br></div>
	</div>
	<div class="jfk-bubble-closebtn-id jfk-bubble-closebtn" tabindex="0"><br></div>
	<div class="jfk-bubble-arrow-id jfk-bubble-arrow jfk-bubble-arrowdown" style="left: 580.5px;">
		<div class="jfk-bubble-arrowimplbefore"><br></div>
		<div class="jfk-bubble-arrowimplafter"><br></div>
	</div>
</div>
<p><br></p>

---end of the HTML doc---
 */