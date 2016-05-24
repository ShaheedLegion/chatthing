#!/bin/env python

import os
import sys

class Options:
  def __init__(self):
    self.name = ''
    self.enum_dir = ''
    self.root_dir = ''
    self.excludes = []

  def ParseCommandLine(self, argv):
    params = []
    for arg in argv[1:]:
      if arg[0] == '-':
        params.append(arg)
      else:
        if not self.enum_dir:
          self.enum_dir = os.path.abspath(arg)
        else:
          raise Exception('enum_dir already specified')


    for p in params:
      p = p.lstrip('-')
      if p.find('=') >= 0:
        parts = p.split('=')
        key = parts[0].lower()
        value = '='.join(parts[1:])
      else:
        key = p
        value = ''

      if key == 'root':
        self.root_dir = os.path.abspath(value)

      if key == 'name':
        self.name = value

      if key == 'exclude':
        for name in value.split(','):
          self.excludes.append(name)

    if not self.enum_dir:
      self.enum_dir = os.getcwd()
    if not os.path.isdir(self.enum_dir):
      raise Exception('enum_dir not found (%s)' % self.enum_dir)

    if not self.root_dir:
      self.root_dir = os.getcwd()
    if not os.path.isdir(self.root_dir):
      raise Exception('root_dir not found (%s)' % self.root_dir)

def GatherFiles(options, path, keys):
  files = dict([(key, [],) for key in keys.keys()])
  files[''] = []
  dirs = []

  for file in os.listdir(path):
    if file[0] == '.':
      continue

    full_path = os.path.join(path, file)

    rel_path = full_path
    if rel_path.startswith(options.root_dir):
      rel_path = rel_path[len(options.root_dir) + 1:]
      rel_path = rel_path.replace('\\', '/')

    must_exclude = False
    for exclude in options.excludes:
      if rel_path.startswith(exclude):
        must_exclude = True
        break
    if must_exclude:
      continue

    if os.path.isdir(full_path):
      dirs.append(full_path)
      continue

    if not file.endswith('.cpp') and not file.endswith('.c') and not file.endswith('.h') and not file.endswith('.mm'):
      continue

    file_key = ''
    for (k, v) in keys.items():
      for end in v:
        if file.endswith(end):
          file_key = k
          break

    files[file_key].append(rel_path)

  if len(dirs):
    for dir in dirs:
      new_files = GatherFiles(options, dir, keys)
      for (k, v) in new_files.items():
        files[k] = files[k] + new_files[k]

  return files

def Main():
  options = Options()
  try:
    options.ParseCommandLine(sys.argv)
  except Exception as e:
    print (e)
    return

  #print 'enum_dir', options.enum_dir
  #print 'root_dir', options.root_dir
  #print 'excludes', options.excludes

  project_name = options.name
  if not project_name:
    project_name = os.path.basename(options.enum_dir)

  keys = {
    '_UNITTEST': ('_unittest.cpp',),
    '_WIN': ('_win.cpp',),
    '_POSIX': ('_posix.cpp',),
    '_LINUX': ('_linux.cpp',),
    '_MAC': ('_mac.cpp', '_mac.mm',),
    '_ANDROID': ('_android.cpp',),
  }
  files = GatherFiles(options, options.enum_dir, keys)

  for (k, v) in files.items():
    if not len(v):
      continue

    print ('set("%s%s_SOURCES"' % (project_name, k,))
    for file in sorted(v):
      print ('  "%s"' % file)
    print (')')
    print
  print ('if(SFML_PLATFORM STREQUAL "win32")')
  print ('  list(APPEND %s_SOURCES ${%s_WIN_SOURCES})' % (project_name, project_name,))
  print ('endif()')
  print
  print ('if(SFML_PLATFORM STREQUAL "linux")')
  print ('  list(APPEND %s_SOURCES ${%s_LINUX_SOURCES})' % (project_name, project_name,))
  print ('  list(APPEND %s_SOURCES ${%s_POSIX_SOURCES})' % (project_name, project_name,))
  print ('endif()')
  print
  print ('if(SFML_PLATFORM STREQUAL "osx")')
  print ('  list(APPEND %s_SOURCES ${%s_MAC_SOURCES})' % (project_name, project_name,))
  print ('  list(APPEND %s_SOURCES ${%s_POSIX_SOURCES})' % (project_name, project_name,))
  print ('endif()')
  print
  print ('if(SFML_PLATFORM STREQUAL "android")')
  print ('  list(APPEND %s_SOURCES ${%s_POSIX_SOURCES})' % (project_name, project_name,))
  print ('  list(APPEND %s_SOURCES ${%s_ANDROID_SOURCES})' % (project_name, project_name,))
  print ('endif()')

if __name__ == '__main__':
  Main()
