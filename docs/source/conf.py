import os
import sys
from datetime import datetime

# Пути к проекту
project = "PrismEngine"
author = "Alexei Kutuzov"
copyright = f"{datetime.now().year}, {author}"

# -- Sphinx настройки ------------------------------------------------
sys.path.insert(0, os.path.abspath("../.."))  # Чтобы видеть исходники C++
extensions = [
    "breathe",          # Мост между Doxygen и Sphinx
    "exhale",           # Автогенерация C++ API
    "sphinx.ext.mathjax",
    "sphinx.ext.viewcode",
]

# -- Breathe настройки ----------------------------------------------
breathe_projects = {
    "PrismEngine": "../../docs/build/doxygen/xml"  # Путь к XML от Doxygen
}
breathe_default_project = "PrismEngine"

# -- Exhale настройки -----------------------------------------------
exhale_args = {
    "containmentFolder":     "./api",
    "rootFileName":          "library_root.rst",
    "rootFileTitle":         "PrismEngine API",
    "doxygenStripFromPath":  "../..",
    "createTreeView":        True,
    "exhaleExecutesDoxygen": True,
    "exhaleDoxygenStdin": """
        INPUT            = ../../src
        EXTRACT_ALL      = YES
        GENERATE_XML     = YES
        RECURSIVE        = YES
        QUIET            = YES
    """
}

# -- Тема и визуальные настройки ------------------------------------
html_theme = "sphinx_rtd_theme"  # Read the Docs (установите через pip)
html_static_path = ["_static"]
html_logo = "_static/logo.png"    # Опционально
html_favicon = "_static/favicon.ico"

# -- Дополнительно -------------------------------------------------
primary_domain = "cpp"
highlight_language = "cpp"