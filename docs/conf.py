import os

project = 'cnda'
copyright = '2024, adminSanderson'
author = 'adminSanderson'
version = '1.0.0'

extensions = [
    'breathe',
]

# Путь к Doxygen XML
source_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))

breathe_projects = {
    'cnda': './doxygen/xml'
}
breathe_default_project = 'cnda'

# Путь к исходным файлам для Breathe
breathe_projects_source_dir = {
    'cnda': f'{source_dir}/include'
}

html_theme = 'sphinx_rtd_theme'
html_static_path = ['_static']