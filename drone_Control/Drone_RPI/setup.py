from distutils.core import setup
from Cython.Build import cythonize

setup(
    name = "udp receiver",
    ext_modules = cythonize("udp_receiver.py")
)
