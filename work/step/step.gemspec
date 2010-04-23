--- !ruby/object:Gem::Specification 
name: step
version: !ruby/object:Gem::Version 
  version: "1.0"
platform: ruby
authors: 
- Bertram Scharpf
autorequire: 
bindir: bin
cert_chain: []

date: 2009-11-12 00:00:00 +01:00
default_executable: 
dependencies: 
- !ruby/object:Gem::Dependency 
  name: autorake
  type: :runtime
  version_requirement: 
  version_requirements: !ruby/object:Gem::Requirement 
    requirements: 
    - - ">="
      - !ruby/object:Gem::Version 
        version: "1.0"
    version: 
description: |
  Simple methods that didn_t manage to become part of standard Ruby.

email: <software@bertram-scharpf.de>
executables: []

extensions: 
- lib/mkrf_conf
extra_rdoc_files: 
- README
- LICENSE
files: 
- lib/mkrf_conf
- lib/Rakefile
- lib/step.c
- lib/step.h
- lib/step/filesys.c
- lib/step/filesys.h
- lib/step/itimer.c
- lib/step/itimer.h
- README
- LICENSE
has_rdoc: true
homepage: http://www.bertram-scharpf.de
licenses: []

post_install_message: 
rdoc_options: []

require_paths: 
- lib
required_ruby_version: !ruby/object:Gem::Requirement 
  requirements: 
  - - ">="
    - !ruby/object:Gem::Version 
      version: "0"
  version: 
required_rubygems_version: !ruby/object:Gem::Requirement 
  requirements: 
  - - ">="
    - !ruby/object:Gem::Version 
      version: "0"
  version: 
requirements: 
- just Ruby
rubyforge_project: step
rubygems_version: 1.3.5
signing_key: 
specification_version: 3
summary: Simple Ruby extensions
test_files: []

