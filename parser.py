#!/usr/bin/env python
#coding=utf-8

# This is a (probably pretty bad) reference implementation
# of an NML parser. Its goal is to be written in the simplest
# way possible, and to be pretty efficient. It also has a 
# rather lackluster command line interface – I know. That's
# because the goal of this particular parser is, again, to be
# simple and readable.
# The parser is pretty light on dependencies – as you can see,
# the only modules it uses are re.match (for regular expressions),
# and sys.argv (for the command line interface). So enjoy reading this,
# I think I've commented it pretty thorougly. Oh, and sorry for all the
# booleans. Since this parses character-by-character, and a lot of stuff is
# dependent on what the next character is, there need to be booleans
# so the parser will know what to do.
# -n

from sys import argv
from re import match

argc = len(argv)

# Pretty self explanatory. I'd just rather type "if match_quote(a)"
# than if a is '"' or a is "'" (especially since the second one looks
# kind of ugly)
def match_quote(str):
	if str is "'" or str is '"':
		return True
	else:
		return False

def minify(x):
	# Delete unnecessary spaces in order to decrease file size (and memory used)
	for (a, b) in enumerate(x):
		if "\n" in b or "\t" in b:
			del x[a]
	return "".join(x)

def preprocess(string):
	new_string = string.split("\n")		# Split by line
	replace_list_huge = []					# List of replace_list_smalls
	to_del = []
	for (a, b) in enumerate(new_string):
		if b.startswith("&"):			# Preprocessor macros are denoted by the "&" character
			replace_list_small = b.split("=")
			replace_list_small[0] = replace_list_small[0].replace("&", "").strip()	# Remove "&" from macro definition
			replace_list_small[1] = replace_list_small[1].strip()						# Strip whitespace
			replace_list_huge.append(replace_list_small)
			to_del.append(b)						# Delete the macro from the buffer before feeding it to parse()
	for (c, d) in enumerate(replace_list_huge):
		exec("""for (p, z) in enumerate(new_string):
				new_string[p] = z.format(%s="%s")""" % (d[0], d[1]))
	for h in to_del:
		del new_string[new_string.index(h)]
	return "\n".join(new_string)		# Join the preprocessed string

# It takes one argument, which is a file object. For some reason, passing argv[1]
# as the file name caused an error.
def parse(file):
	tokens = str()
	# "buffer" is, predictably, the buffer that actually holds the output. It's
	# an array because Python strings are non-mutable; so, in order to modify it
	# as it's being parsed, it has to be a list.
	buffer = []
	open = ["head", "body"]
	# Close tag on whitespace?
	ws = False
	# Same as ws, but for "@" tags.
	ws2 = False
	# Are we doing item attributes now?
	ac = False
	ac2 = False
	# Check for space. Used for attributes (space after ":")
	cfs = False
	# Ignore quotes
	iq = True
	# End comment on newline
	ce = False
	css = False
	buffer.append("<!DOCTYPE html><html>")		# Always start with the doctype (and html tag)!
	for a in file:
		if a is "$":
			# Replace "$" with "<" and set the ws flag.
			buffer.append("<")
			ws = True
		elif a is "@":
			# Replace "@" with "<" and set the ws2 flag.
			buffer.append("<")
			ws2 = True
		elif ws and match("\s", a):
			# The space after a $tag should actually be a ">".
			# ($div should be <div>)
			buffer.append(">")
			open.append(tokens)
			ws = False
			tokens = ""
		elif ws2 and iq and match("\s", a):
			# The space between an @tag and its value should actually be a ">".
			# (@h1 "Hi" should be <h1>Hi</h1>)
			buffer.append(">")
			ws2 = False
		elif a is "(":
			# From now until we see a "(", everything is an attribute.
			ac = True
		elif ac:
			z = len(buffer) - 1
			# Replace the last ">" with the first character of the attribute
			buffer[z] = a
			# Insert a space between the tag name and the first attribute
			buffer.insert(z, " ")
			ac = False
			ac2 = True
			del z			# Delete "z" to save memory
		elif match_quote(a):
			if not iq:
				# If we're not supposed to ignore quotes (read: we have a pair open),
				# replace the next quote we find with a closing tag for the open @tag.
				buffer.append("</%s>" % tokens)
				tokens = ""
				ws2 = False
			iq = not iq				# Toggle the flag to ignore quotes
		elif ac2 and a is ":":
			# In NML, attribute syntax is name: value. In HTML, it's name="value".
			# So, replace the colon with '="' and ignore the next character (ONLY if it's a space!)
			buffer.append('="')
			cfs = True
		elif cfs and match("\s", a):
			cfs = False
		elif ac2 and a is "," and iq:
			# Commas separate attributes when there are two or more of them. 
			# So close the quotes if we're starting a new attribute.
			buffer.append('"')
		elif ac2 and a is ")":
			buffer.append('">')	# Close quotes for the last attribute when attributes are closed
		elif a is "%":
			buffer.append("</%s>" % open.pop())
		elif a is "#":
			# Replace a "#" with "<!--" (The start of an HTML comment)
			# OR, if --comment-strip is specified, delete it
			buffer.append("<!--")
			ce = True
		elif ce and "\n" in a:
			buffer.append("-->")
			ce = False
		else:
			# If the whitespace isn't marked as significant through the
			# use of the "ws" flag, don't add it to the buffer!
			if not ws or not match("\s", a): buffer.append(a)
		# Don't add "$" or "@" to the tag name, otherwise you'd get </$body> or </@h1>
		if (ws or ws2) and a is not "$" and a is not "@": tokens += a
	return (minify(buffer) + "</html>")		# Make "buffer" a string and close the "html" tag from the beginning

if argc is 2:
	m = open(argv[1], "r")
	print parse(preprocess(m.read()))
	m.close()
else:
	# Print the help message
	print "\033[1mUsage:\033[0m %s [file]" % argv[0]
