This is a Visual Studio project of Bounded Biharmonics Weights shape deformation.
I use libigl (https://github.com/libigl/libigl). I don't remember which libigl version I use, but it is probably early 2014 version. 

How to build on Windows:
* Build tetgen using CMAKE
* I use MOSEK 7.1. If you are a university student, you can get it free here: https://license.mosek.com/academic/
* The last dependency is Eigen 3.2

To set up the Visual Studio project, left click on the name of the project. Select "Properties".
On "C/C++" "General" "Additional Directories":
* __your-path__\BBW\BBW_LIBIGL;D:\Code\BBW\BBW_LIBIGL\igl
* __your-path__\BBW\BBW_LIBIGL\igl\tetgen;D:\Code\BBW\tetgen1.5.0
* __your-path__\Eigen_3_2;D:\Code\Eigen_3_2\unsupported
* C:\Program Files (x86)\Mosek\7\tools\platform\win32x86\h

On "Librarian" "General" "Additional Dependencies":
* tet.lib
* mosek7_1.lib
* mosekscopt7_1.lib

On "Librarian" "General" "Additional Library Directories":
* __your-path__\BBW\tetgen1.5.0\bin\Debug
* C:\Program Files (x86)\Mosek\7\tools\platform\win32x86\bin
