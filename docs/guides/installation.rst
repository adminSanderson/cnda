Installation
=============

This guide covers building **cnda** on Windows, macOS, and Linux.

Requirements
------------

Before building, you need:

- **C Compiler**: GCC or compatible (Clang, MSVC)
- **Make**: GNU Make or compatible tool
- **Git**: To clone the repository

Platform-Specific Setup
------------------------

Windows
~~~~~~~

**Option 1: Using MinGW (Recommended)**

1. Download MinGW-w64 from `https://www.mingw-w64.org/ <https://www.mingw-w64.org/>`_

2. Install MinGW with these components:
   
   - gcc (C compiler)
   - mingw32-make (GNU Make)
   - binutils (ar, ranlib for archive creation)

3. Add MinGW to your PATH:
   
   - Right-click "This PC" → Properties
   - Advanced system settings → Environment Variables
   - Add MinGW bin folder to PATH (e.g., ``C:\mingw64\bin``)

4. Verify installation:

   .. code-block:: bash

      gcc --version
      mingw32-make --version

**Option 2: Using WSL2 (Windows Subsystem for Linux)**

If you prefer a Linux environment on Windows:

.. code-block:: bash

   # Enable WSL2 in PowerShell (Admin)
   wsl --install

   # Then follow Linux instructions below

**Option 3: Using Visual Studio (Advanced)**

You can also use MSVC, but you'll need to adjust the Makefile.

macOS
~~~~~

Install Xcode Command Line Tools:

.. code-block:: bash

   xcode-select --install

This includes gcc, clang, and make.

**Verify installation:**

.. code-block:: bash

   gcc --version
   make --version

Linux
~~~~~

**Ubuntu/Debian:**

.. code-block:: bash

   sudo apt update
   sudo apt install build-essential git

This includes gcc, make, and other development tools.

**Fedora/RHEL:**

.. code-block:: bash

   sudo dnf install gcc make git

**Arch Linux:**

.. code-block:: bash

   sudo pacman -S base-devel git

**Verify installation:**

.. code-block:: bash

   gcc --version
   make --version

Building the Library
---------------------

**1. Clone the Repository**

.. code-block:: bash

   git clone https://github.com/adminSanderson/cnda
   cd cnda

**2. Build the Library**

.. code-block:: bash

   make lib

This creates ``libcnda.a`` (static library) in the project root.

**On Windows with MinGW, use:**

.. code-block:: bash

   mingw32-make lib

**Output:**

- ``libcnda.a`` - Static library (all platforms)
- ``build/`` - Compiled object files

**3. Run Tests (Optional)**

Verify the build is working:

.. code-block:: bash

   make test

Or on Windows:

.. code-block:: bash

   mingw32-make test

This compiles and runs all test files in the ``tests/`` directory.

**4. Clean Build (Optional)**

To remove build artifacts:

.. code-block:: bash

   make clean

This removes ``build/`` directory and ``libcnda.a``.

Using the Library
------------------

Once built, link ``libcnda.a`` to your project:

**Example: Compile a program using cnda**

.. code-block:: bash

   gcc -Iinclude program.c -L. -lcnda -lm -o program

**Explanation:**

- ``-Iinclude`` - Add header directory to include path
- ``-L.`` - Add current directory to library search path
- ``-lcnda`` - Link against libcnda.a
- ``-lm`` - Link math library (required for math.h functions)
- ``-o program`` - Output executable name

**Example C Program:**

.. code-block:: c

   #include "cnda.h"

   int main() {
       size_t shape[2] = {3, 4};
       NDArray* arr = nda_zeros(2, shape);
       
       nda_print(arr, 2);
       nda_free(arr);
       
       return 0;
   }

**Windows (MinGW):**

.. code-block:: bash

   gcc -Iinclude program.c -L. -lcnda -lm -o program.exe
   program.exe

Installation Troubleshooting
------------------------------

**"gcc: command not found"**

- **Windows**: MinGW not in PATH. Check installation and PATH environment variable.
- **macOS**: Run ``xcode-select --install`` again
- **Linux**: Install build-essential or equivalent for your distro

**"make: command not found"**

- Install GNU Make (included in build tools for all platforms)

**Linker errors when using library**

Make sure:

1. You built the library: ``make lib``
2. ``libcnda.a`` exists in project root
3. You included ``-L.`` when compiling your program
4. You included ``-lcnda`` in linker flags
5. You included ``-lm`` for math library

**On Windows, "ar: command not found"**

- ar should come with MinGW binutils. Check PATH or reinstall MinGW with binutils selected.

Next Steps
----------

After installation, check out the:

- :doc:`Quick Start Guide </guides/quickstart>` for basic usage
- :doc:`API Reference </api/core>` for all available functions

Getting Help
------------

If you encounter issues:

1. Check that all requirements are installed
2. Verify compiler version: ``gcc --version``
3. Try ``make clean`` then ``make lib`` again
4. Check GitHub issues: https://github.com/adminSanderson/cnda/issues
5. Create a new issue with your error message