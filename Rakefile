#!/usr/bin/env ruby

# We use rake-compiler for this project.
require 'rake/extensiontask'

extensions = Dir['ext/**/extconf.rb'].map{ |f| File.dirname(f) }

extensions.each do |ext_dir|
  name    = ext_dir.sub('ext/', '') #.gsub('/', '_')
  lib_dir = File.join('lib/carats')

  Rake::ExtensionTask.new(name) do |ext|
    ext.ext_dir = ext_dir
    ext.lib_dir = lib_dir
    ext.tmp_dir = 'tmp'
  end
end

