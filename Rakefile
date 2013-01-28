#!/usr/bin/env ruby

# We use rake-compiler for this project.
require 'rake/extensiontask'

lib_dir = 'lib/carats/core_ext'

Dir['ext/**/*.c'].each do |ext|
  next unless File.exist?(File.dirname(ext) + '/extconf.rb')

  ext_name = File.basename(ext).chomp('.c')
  ext_dir  = File.dirname(ext)

  Rake::ExtensionTask.new(ext_name) do |ext|
    ext.ext_dir = ext_dir
    ext.lib_dir = lib_dir
    ext.tmp_dir = 'tmp'
  end
end

