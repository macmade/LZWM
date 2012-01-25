# ------------------------------------------------------------------------------
# 
# Copyright (c) 2010, Jean-David Gadina <macmade@eosgarden.com>
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# 
#  -   Redistributions of source code must retain the above copyright notice,
#      this list of conditions and the following disclaimer.
#  -   Redistributions in binary form must reproduce the above copyright
#      notice, this list of conditions and the following disclaimer in the
#      documentation and/or other materials provided with the distribution.
#  -   Neither the name of 'Jean-David Gadina' nor the names of its
#      contributors may be used to endorse or promote products derived from
#      this software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
# 
# ------------------------------------------------------------------------------
# 
# IMPORTANT NOTE:
# 
# This makefile is used for the configuration of language specific options.
# It's not supposed to be called directly by the make command.
# 
# Please note that you need at least version 3.81 of GNU Make to use this file.
# Older versions are not supported and will never be.
# 
# You also need a copy of the GNU Libtool in order to handle the shared objects.
# GNU Libtool is sometimes called glibtool, or simply libtool.
# Others implementations of Libtool are not supported at the time.
# 
#-------------------------------------------------------------------------------

# $Id$

# Flag to let the makefile knows that the code specific options were included
CODE_HASOPTIONS         := 1

#-------------------------------------------------------------------------------
# Extensions for files
#-------------------------------------------------------------------------------

EXT_CODE                = .c
EXT_HEADERS             = .h
EXT_LIB_OBJECT          = .lo
EXT_LIB_ARCHIVE         = .la
EXT_OBJECT              = .o

#-------------------------------------------------------------------------------
# Compiler tools
#-------------------------------------------------------------------------------

CC                      = clang
LIBTOOL                 = glibtool

#-------------------------------------------------------------------------------
# Arguments for the compiler tools
#-------------------------------------------------------------------------------

ARGS_CC                 = -Os -Wabi -Waddress-of-temporary -Waddress -Waggregate-return -Wall -Wambiguous-member-template -Warc-abi -Warc-non-pod-memaccess -Warc-retain-cycles -Warc-unsafe-retained-assign -Warc -Watomic-properties -Wattributes -Wavailability -Wbad-function-cast -Wbind-to-temporary-copy -Wbitwise-op-parentheses -Wbool-conversions -Wbuiltin-macro-redefined -Wc++-compat -Wc++0x-compat -Wc++0x-extensions -Wcast-align -Wcast-qual -Wchar-align -Wchar-subscripts -Wcomment -Wcomments -Wconditional-uninitialized -Wconversion -Wctor-dtor-privacy -Wcustom-atomic-properties -Wdeclaration-after-statement -Wdefault-arg-special-member -Wdelegating-ctor-cycles -Wdelete-non-virtual-dtor -Wdeprecated-declarations -Wdeprecated-implementations -Wdeprecated-writable-strings -Wdeprecated -Wdisabled-optimization -Wdiscard-qual -Wdiv-by-zero -Wduplicate-method-arg -Weffc++ -Wempty-body -Wendif-labels -Wexit-time-destructors -Wextra-tokens -Wextra -Wformat-extra-args -Wformat-nonliteral -Wformat-zero-length -Wformat -Wformat=2 -Wfour-char-constants -Wglobal-constructors -Wgnu-designator -Wgnu -Wheader-hygiene -Widiomatic-parentheses -Wignored-qualifiers -Wimplicit-atomic-properties -Wimplicit-function-declaration -Wimplicit-int -Wimplicit -Wimport -Wincompatible-pointer-types -Winit-self -Winitializer-overrides -Winline -Wint-to-pointer-cast -Winvalid-offsetof -Winvalid-pch -Wliteral-range -Wlocal-type-template-args -Wlogical-op-parentheses -Wlong-long -Wmain -Wmicrosoft -Wmismatched-tags -Wmissing-braces -Wmissing-declarations -Wmissing-field-initializers -Wmissing-format-attribute -Wmissing-include-dirs -Wmissing-noreturn -Wmost -Wmultichar -Wnested-externs -Wnewline-eof -Wnon-gcc -Wnon-virtual-dtor -Wnonfragile-abi2 -Wnonnull -Wnull-dereference -Wobjc-nonunified-exceptions -Wold-style-cast -Wold-style-definition -Wout-of-line-declaration -Woverflow -Woverlength-strings -Woverloaded-virtual -Wpacked -Wparentheses -Wpointer-arith -Wpointer-to-int-cast -Wprotocol -Wreadonly-setter-attrs -Wredundant-decls -Wreorder -Wreturn-type -Wself-assign -Wsemicolon-before-method-body -Wsequence-point -Wshadow -Wshorten-64-to-32 -Wsign-compare -Wsign-promo -Wsizeof-array-argument -Wstack-protector -Wstrict-aliasing -Wstrict-overflow -Wstrict-prototypes -Wstrict-selector-match -Wsuper-class-method-mismatch -Wswitch-default -Wswitch-enum -Wswitch -Wsynth -Wtautological-compare -Wtrigraphs -Wtype-limits -Wundeclared-selector -Wuninitialized -Wunknown-pragmas -Wunnamed-type-template-args -Wunneeded-internal-declaration -Wunneeded-member-function -Wunused-argument -Wunused-exception-parameter -Wunused-function -Wunused-label -Wunused-member-function -Wunused-parameter -Wunused-value -Wunused-variable -Wunused -Wused-but-marked-unused -Wvariadic-macros -Wvector-conversions -Wvla -Wvolatile-register-var -Wwrite-strings
ARGS_LIBTOOL_COMPILE    = --tag=CC --mode=compile
ARGS_LIBTOOL_LINK       = --tag=CC --mode=link
