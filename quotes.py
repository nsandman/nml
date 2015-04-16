import re

x = 'Hello to all the "children" of the \'world\''
print re.findall('["|\']\w+["|\']+', x)