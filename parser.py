#!/usr/bin/env python

from sys import argv
from re import match

file = open(argv[1], "r")

tokens = str()
buffer = []

open = ["head", "body"]

def match_quote(str):
	if str is "'" or str is '"':
		return True
	else:
		return False

def minify(x):
	# Remove unnecessary spaces and stuff
	return "".join(x)

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

buffer.append("<!DOCTYPE html>")
for a in file.read():
	if a is "$":
		buffer.append("<")
		ws = True
	elif a is "@":
		buffer.append("<")
		ws2 = True
	elif ws and match("\s", a):
		buffer.append(">")
		open.append(tokens)
		ws = False
		tokens = ""
	elif ws2 and iq and match("\s", a):
		buffer.append(">")
		ws2 = False
	elif a is "(":
		ac = True
	elif ac:
		buffer[len(buffer)-1] = a
		buffer.insert(len(buffer)-1, " ")
		ac = False
		ac2 = True
	elif match_quote(a):
		if not iq:
			buffer.append("</%s>" % tokens)
			tokens = ""
			ws2 = False
		iq = not iq
	elif ac2 and a is ":":
		buffer.append('="')
		cfs = True
	elif cfs and match("\s", a):
		cfs = False
	elif ac2 and a is ",":
		buffer.append('"')
	elif ac2 and a is ")":
		buffer.append('">')
	elif a is "%":
		buffer.append("</%s>" % open.pop())
	else:
		if not ws or not match("\s", a): buffer.append(a)

	if (ws or ws2) and a is not "$" and a is not "@": tokens += a

print minify(buffer)

file.close()