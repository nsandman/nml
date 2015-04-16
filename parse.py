#!/usr/bin/python

import sys, re

y = open(sys.argv[1], 'r')
bracketize = True
element = ['body', 'head']
notclose = ['br', 'hr', 'img']
times = 0
result = str()
for a in y:
	already = False
	a = a.strip()
	if times == 0:
		a = a.replace('nml', '<!DOCTYPE html><html>')
	elif a.startswith('js'):
		if not a.startswith('js from '):
			a = '<script type="text/javascript">'
			bracketize = False
			element.append('script')
		else:
			a = '<script type="text/javascript" src="' + a[8:] + '"></script>'
	elif a.startswith('css'):
		if not a.startswith('css from '):
			a = '<style type="text/css">'
			bracketize = False
			element.append('style')
		else:
			a = '<link rel="stylesheet" type="text/css" href="' + a[9:] + '" />'
	elif a[0] == '%':
			bracketize = True
			a = '</' + element.pop(len(element) - 1) + '>'
	else:
		if bracketize:
			t = str()
			d = a.split('.')
			if len(d) != 1:
				t = d[1]
			if a.startswith('#'):
				a = '!-- ' + a[1:] + ' --'
				already = True
			elif a.startswith('body') or a.startswith('nml') or a.startswith('head'):
				already = True
			f = re.findall('(?<="|\')\w+(?="|\')', a)			
			if len(f) == 0:
				if a not in notclose:
					a = '<' + a + '>'
					if not already:
						element.append(a)
				else:
					a = '<' + a + ' />'
			else:
				a = '<' + a.split()[0] + ' ' + t.strip() + '>' + f[0] + '</' + a.split()[0] + '>'
	result += a
	times += 1
result += '</html>'
y.close()
e = open(sys.argv[2], 'w')
e.write(result)
e.close()