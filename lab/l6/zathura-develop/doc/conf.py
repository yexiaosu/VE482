#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# SPDX-License-Identifier: Zlib

import sphinx_rtd_theme

# -- General configuration ------------------------------------------------

extensions     = [
    'sphinx.ext.todo',
    'breathe'
]
source_suffix  = '.rst'
master_doc     = 'index'
templates_path = ['_templates']
exclude_patterns = ['_build']

pygments_style = 'sphinx'


# -- Project configuration ------------------------------------------------

project   = 'zathura'
copyright = '2014, pwmt.org'
version   = '0.2.7'
release   = '0.2.7'


# -- Options for HTML output ----------------------------------------------

html_theme        = 'sphinx_rtd_theme'
html_theme_path   = [sphinx_rtd_theme.get_html_theme_path()]
html_static_path  = ['_static']
htmlhelp_basename = 'zathuradoc'

# -- Options for breathe ---------------------------------------

breathe_projects = { "zathura": "_build/doxygen/xml" }
breathe_default_project = "zathura"
breathe_build_directory = "_build"
breathe_projects_source = {
    "zathura": "../"
}
breathe_domain_by_extension = {
    "h" : "c",
    "c" : "c"
}
