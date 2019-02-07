### Evaluate JSON data to create SQLite entries and populate a database.


from collections import namedtuple
from json        import loads
from os          import walk
from sqlite3     import connect
from subprocess  import Popen
from time        import sleep


db = 'ads.db'


# String to tuple
def s2t(s):
  return loads(s, object_hook = \
                  lambda d: namedtuple('x', d.keys())(*d.values()))

# Tuple to dict
def t2d(t):
  stypes = (bool, int, float, str)
  d = dict(t._asdict())
  for k, v in d.items():
    if type(v) == list:
      for i in range(len(v)):
        if type(v[i]) not in stypes:
          d[k][i] = t2d(v[i])
      continue
    if type(v) not in stypes:
      d[k] = t2d(v)
  return d


# Create and fill db tables with data
def fill(c, d, n, i):
  c.execute('create table if not exists '+n+'(id int not null)')

  keys = ''
  vals = ''
  for k, v in d.items():
    if type(v) == dict:
      fill(c, v, k, i)
      continue

    if type(v) == list:
      for t in v:
        if type(t) == dict:
          fill(c, t, k, i)
        else:
          fill(c, {k : t}, k, i)
      continue

    if type(v) == str:
      v = v.replace('\'', '\'\'')

    cols = c.execute('pragma table_info('+n+')')
    found = False
    for col in cols:
      if k == col[1]:
        found = True
        break
    if not found:
      c.execute('alter table '+n+' add column '+k+' '+str(type(v))[8:-2])

    quote = ('\'' if type(v) in (bool, str) else '')
    keys += ', ' + k
    vals += ', ' + quote + str(v) + quote
  c.execute('insert into '+n+' (id'+keys+') values ('+str(i)+vals+')')


Popen('rm '+db, shell=True)
Popen('touch '+db, shell=True)
con = connect(db)
c = con.cursor()
tot = 0
err = 0

for root, dirs, files in walk('json'):
  tot = len(files)
  i = 0
  for fil in files:
    i += 1
    d = {}

    try:
      f = open(root + '/' + fil, 'r')
      d = t2d(s2t(f.read()))
      f.close()
      if 'id' in d.keys():
        fill(c, d, 'ad', d['id'])
      if i == 1 or i % (tot // 10) == 0:
        print('json->sqlite %d%% done' % (round(i*100/tot)))

    except Exception as e:
      err += 1
      print('Problem inserting: ' + fil + '\nException: ' + str(e) + \
            '\nJSON:\n' + str(d))


con.commit()
c.close()

print('%d of %d jsons were stored (%.2f%%)' % (tot-err, tot, (tot-err)*100/tot))
