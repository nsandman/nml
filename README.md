#NML
NML is a simple preprocessor for HTML that makes it easier to write. In this document, you will learn how to write and read it. You can also read "parse.py" if you want to learn how it is parsed.

##Sample NML Page
NML is just an HTML preprocessor. This means that it is "compiled" into plain HTML.

Here is an example.

```
$nml
	$head
		title 'Hello World'
	%
	$body
		h1 'Hello World'
	%
%

```

This looks simple, and it is.