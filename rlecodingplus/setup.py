#https://stackoverflow.com/questions/18423512/calling-c-code-from-python-using-cython-whith-the-distutilis-approach
#https://smyt.ru/blog/sozdaem-s-python-rasshireniya-s-pomshyu-pybind11/

# файл для установки модуля с помощью pip в глобальной среде (чей pip - в той среде и установится) 
# или для сборки модуля (все файлы будут в папке проекта) через python setup.py build_ext -i
import os, sys

from distutils.core import setup, Extension
from distutils import sysconfig

cpp_args = ['-std=c++11', '-stdlib=libc++', '-mmacosx-version-min=10.7']

sfc_module = Extension(
    'rlecodingplus', sources = ['module.cpp'], # указываем код расширения
    include_dirs=['C:/OSGeo4W64/apps/Python37/include/pybind11/include', 'C:/OSGeo4W64/apps/Python37/include/pybind11','C:/opencv/opencv/build/include', 'C:/opencv/opencv/build/include/opencv2'], # библиотеки, используемые в проекте
    language='c++',
    library_dirs=['C:/opencv/opencv/build/x64/vc14/lib'], # путь к файлам .lib библиотеки opencv
    libraries=['opencv_world411', 'opencv_world411d'], # название .lib файлов
    #extra_compile_args = cpp_args,
    )

setup(
    name = 'rlecodingplus', # имя, под которым будет вызываться модуль
    version = '1.0',
    description = 'Python package with rlecodingplus C++ extension (PyBind11)',
    ext_modules = [sfc_module],
)