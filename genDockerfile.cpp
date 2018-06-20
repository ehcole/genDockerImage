#include <iostream>
#include <string.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
using namespace std;

int main(int argc, char** argv) {
	if (argc < 7) {
		cout << "usage: ./genDockerfile GCC_VERSION MPI_VERSION TPL_URL TPL_BUILD_DIR [NAME] [ZIP]" << endl;
		return 1;
	}
	string gccVersion = argv[1];
	string mpiVersion = argv[2];
	string argv4 = argv[4];
	string cmakeDir;
	if (argv4[0] != '/') {
	  cmakeDir = "/scratch/" + argv4;
	}
	else {
	  cmakeDir = "/scratch" + argv4;
	}
	if (argv[1][0] != 'g') {
	  cout << "GCC_VERSION should be of the form  \"gcc-x.y.z\"" << endl;
	  cout << "Using default GCC_VERSION: gcc-6.4.0" << endl;
	  gccVersion = "gcc-6.4.0";
	}
	else {
	  gccVersion = argv[1];
	}
	if (strstr(argv[2], "mpich") == NULL && strstr(argv[2], "mvapich") == NULL) {
	  cout << "MPI_VERSION should be of the form \"mpich-x.y\" or \"mvapich2-x.y\"" << endl;
	  cout << "Using default MPI_VERSION: mvapich2-2.0" << endl;
	  mpiVersion = "mvapich2-2.0";
	}
	else {
	  mpiVersion = argv[2];
	}
	ofstream output;
	output.open("Dockerfile");
	string TPLs = argv[3];	
	if (TPLs.find("git") == string::npos) {
	  cout << "Invalid TPL_URL. Must be a git repo. Using default value: https://github.com/CASL/vera_tpls.git" << endl;
	  TPLs = "https://github.com/CASL/vera_tpls.git";
	  cmakeDir = "/scratch/vera_tpls/TPL_build/";
	}
	/////begin writing Dockerfile
	//setting variables/parameters
	output << "FROM centos:7" << endl;
	output << "ARG NPROC=2" << endl;
	output << "WORKDIR /scratch" << endl;
	output << "ENV DEVTOOL_INSTALL_DIR=/opt/mpact-dev-env  \\ "<< endl;
	output << "GCC_VERSION=" + gccVersion + " \\ " << endl;
	output << "EXPECT_SH=expect.sh						 	\\ "<< endl;
	output << "PYTHON_3=/etc/modulefiles/python-anaconda3/3.6.4  		\\ "<< endl;
	output << "CMAKE=/etc/modulefiles/cmake/3.3.2  \\ "<< endl;
	output << "MPI_VERSION=" + mpiVersion + "  \\ "<< endl;
	output << "VERA_TPL_INSTALL_DIR=/opt/mpact-dev-env/" + gccVersion + "/tpls/ \\ "<< endl;
	output << "VERA_SCRATCH_DIR=/scratch/tmp \\ "<< endl;
	output << "MKL=/etc/modulefiles/mkl/2018 \\ " << endl;
	output << "FINISH_BUILD=/scratch/finishBuild.sh" << endl;

	//docker build commands begin here

	//installing packages
	output << "RUN yum install -y epel-release && yum repolist       		&&  \\ "<< endl;
	output << "yum update -y                                       		&&  \\ "<< endl;
	//installs mkl packages if not using vera_tpls
	if (TPLs.find("vera") == string::npos) {
	  output << "yum-config-manager --add-repo https://yum.repos.intel.com/setup/intelproducts.repo && \\ " << endl;
	  output << "rpm --import https://yum.repos.intel.com/intel-gpg-keys/GPG-PUB-KEY-INTEL-SW-PRODUCTS-2019.PUB && \\ " << endl;
	  output << "yes | yum repolist && \\ " << endl;
	  output << "yum install -y intel-mkl && \\ " << endl;
	}
	output << "yum group install \"Development Tools\" -y            		&&  \\ "<< endl;
	output << "yum install valgrind cmake htop environment-modules -y &&  \\ "<< endl;
	output << "yum install latexmk doxygen-latex texlive-titling texinfo texlive-titlesec -y 		&&  \\ "<< endl;
	output << "yum install libXext-devel -y						&&  \\ "<< endl;
	output << "yum install python papi-devel -y						&&  \\ "<< endl;
	output << "yum install " + mpiVersion + "-devel -y						&&  \\ "<< endl;
	output << "yum install hwloc-devel.x86_64	-y					&&  \\ "<< endl;
	output << "yum install libibmad-devel.x86_64 -y					&&  \\ "<< endl;
	output << "yum install -y valgrind cmake graphviz \\ "<< endl;
	output << "htop environment-modules   \\ "<< endl;
	output << "vim nano emacs  \\ "<< endl;
	output << "libXext-devel  \\ "<< endl;
	output << "python \\ "<< endl;
	output << "yum install -y git	&&  \\ "<< endl;
	output << "yum install -y wget		&&  \\ "<< endl;
	output << "yum install -y bzip2	&&  \\ "<< endl;
	output << "yum install openssl-devel	 -y				    &&  \\ "<< endl;
	output << "yum install -y cmake						  &&  \\ "<< endl;
	output << "export PATH=/usr/lib64/" + mpiVersion + "/bin:$PATH &&  \\ "<< endl;

	//cloning TriBITS
	output << "git clone https://github.com/TriBITSPub/TriBITS.git &&  \\ "<< endl;
	output << "mkdir -p ${DEVTOOL_INSTALL_DIR}/common_tools &&  \\ "<< endl;
	output << "cp -r TriBITS/tribits/python_utils/gitdist  /opt/mpact-dev-env/common_tools/ &&   \\ "<< endl;

	//installing anaconda3 and writing module file
	output << "wget https://repo.continuum.io/archive/Anaconda3-5.1.0-Linux-x86_64.sh	 &&  \\ "<< endl;
	//this convoluted command interacts with the anaconda installation process
	output << "(for i in {1..4}; do echo yes; done; echo no) | bash Anaconda3-5.1.0-Linux-x86_64.sh			    	&&  \\ "<< endl;
	output << "mkdir -p /etc/modulefiles/python-anaconda3		 &&  \\ "<< endl;
	output << "touch /etc/modulefiles/python-anaconda3/3.6.4		 &&  \\ " << endl;
	output << "echo \"#%Module\" >> ${PYTHON_3}					&&  \\ " << endl;
	output << "echo \"set version 3.6.4\" >> ${PYTHON_3}			&&  \\ "<< endl;
	output << "echo \'set name \"Anaconda distribution of Python - \\$version\"\' >> ${PYTHON_3}						&&  \\ "<< endl;
	output << "echo \'set msg \"\"\' >> ${PYTHON_3}				&&  \\ "<< endl;
	output << "echo >> ${PYTHON_3}						&&  \\ "<< endl;
	output << "echo \"proc ModulesHelp { } {\" >> ${PYTHON_3}		&&  \\ "<< endl;
	output << "echo \' puts stderr \"Anaconda Python 3 Distribution\"\' >> ${PYTHON_3}								&&  \\ "<< endl;
	output << "echo \' puts stderr \"\"\' >> ${PYTHON_3}			&&  \\ "<< endl;
	output << "echo \' puts stderr \"The Anaconda Python 3 distribution is a completely free, enterprise-ready Python\"\' >> ${PYTHON_3}	&&  \\ "<< endl;
	output << "echo \' puts stderr \"distribution for large-scale data processing, predictive analytics, and\"\' >> ${PYTHON_3} &&  \\ "<< endl;
	output << "echo \' puts stderr \"scientific computing.  This software module contains the commercially licensed,\"\' >> ${PYTHON_3}	&&  \\ "<< endl;
	output << "echo \' puts stderr \"accelerated versions of MKL, NumPy, SciPy, NumbaPro, and CUDA for Python; it\"\' >> ${PYTHON_3}	&&  \\ "<< endl;
	output << "echo \' puts stderr \"also has the commercial IOPro package which loads NumPy arrays (and Pandas\"\' >> ${PYTHON_3}		&&  \\ "<< endl;
	output << "echo \' puts stderr \"DataFrames) directly from files, SQL databases, and NoSQL stores, without\"\' >> ${PYTHON_3}	&&  \\ "<< endl;
	output << "echo \' puts stderr \"creating millions of temporary, intermediate Python objects, or requiring\"\' >> ${PYTHON_3}	&&  \\ "<< endl;
	output << "echo \' puts stderr \"expensive array resizing operations; IOPro provides a drop-in replacement for\"\' >> ${PYTHON_3}	&&  \\ "<< endl;
	output << "echo \' puts stderr \"the NumPy functions loadtxt() and genfromtxt(), but drastically improves\"\' >> ${PYTHON_3} &&  \\ "<< endl;
	output << "echo \' puts stderr \"\"' >> ${PYTHON_3}			&&  \\ "<< endl;
	output << "echo \' puts stderr \"To create your own Python environment using this module, see\"\' >> ${PYTHON_3}				&&  \\ "<< endl;
	output << "echo \' puts stderr \"http://conda.pydata.org/docs/using/envs.html\"\' >> ${PYTHON_3}	 &&  \\ "<< endl;
	output << "echo \' puts stderr \"\"\' >> ${PYTHON_3}			&&  \\ "<< endl;
	output << "echo \' puts stderr \"In addition to installing Python packages into your own Python environment\"\' >> ${PYTHON_3}	     &&  \\ "<< endl;
	output << "echo \' puts stderr \"using the \"conda install\" command as described on the web page above, you\"\' >> ${PYTHON_3}  &&  \\ "<< endl;
	output << "echo \' puts stderr \"can install Python packages using the \"pip\" command.  For example, to install\"\' >> ${PYTHON_3}     &&  \\ "<< endl;
	output << "echo \' puts stderr \"a Python package named \"Foo\", run\"\' >> ${PYTHON_3}				      &&  \\ "<< endl;
	output << "echo \' puts stderr \"\"' >> ${PYTHON_3}			&&  \\ "<< endl;
	output << "echo \' puts stderr \"    pip install Foo --user\"\' >> ${PYTHON_3} 										&&  \\ "<< endl;
	output << "echo \' puts stderr \"\" }\' >> ${PYTHON_3}			&&  \\ "<< endl;
	output << "echo >> ${PYTHON_3}						&&  \\ "<< endl;
	output << "echo \'module-whatis \"Name: Anaconda Python 3\"\' >> ${PYTHON_3} &&  \\ "<< endl;
	output << "echo \'module-whatis \"Description: Python 3 distribution for scientific computing, including accelerated commercial versions of several Python packages.\"\' >> ${PYTHON_3}		&&  \\ "<< endl;
	output << "echo \'module-whatis \"License information: Academic Cluster License, https://docs.continuum.io/anaconda/eula\"\' >> ${PYTHON_3} 										&&  \\ "<< endl;
	output << "echo \'module-whatis \"Category: Python, programming, scripting, numpy, scipy, matplotlib, biopython, astropy, IPython, Jupyter\"\' >> ${PYTHON_3}	     	&&  \\ "<< endl;
	output << "echo \'module-whatis \"Package documentation: https://docs.continuum.io/\"\' >> ${PYTHON_3}			&&  \\ "<< endl;
	output << "echo \'module-whatis \"Version: \\$version\"\' >> ${PYTHON_3}	&&  \\ "<< endl;
	output << "echo >> ${PYTHON_3}						&&  \\ "<< endl;
	output << "echo >> ${PYTHON_3}						&&  \\ "<< endl;
	output << "echo \"#Set the paths & vars for Anaconda\" >> ${PYTHON_3} &&  \\ "<< endl;
	output << "echo \"set root /opt/mpact-dev-env/common_tools/anaconda3\" >> ${PYTHON_3}	&&  \\ "<< endl;
	output << "echo \"prepend-path PATH          \\$root/bin\" >> ${PYTHON_3} &&  \\ "<< endl;
	output << "echo \"prepend-path MANPATH       \\$root/man\" >> ${PYTHON_3} &&  \\ "<< endl;
	output << "echo \"setenv       ANACONDA_ROOT \\$root\" >> ${PYTHON_3} &&  \\ "<< endl;
	output << "echo >> ${PYTHON_3}						&&  \\ "<< endl;
	output << "echo \"conflict python-anaconda2\" >> ${PYTHON_3}	     &&  \\ "<< endl;
	output << "echo >> ${PYTHON_3} 						&&  \\ "<< endl;
	output << "echo \"prereq mpi\" >> ${PYTHON_3}				&&  \\ "<< endl;

	//installing cmake and writing module file
	output << "wget https://cmake.org/files/v3.3/cmake-3.3.2.tar.gz   &&  \\ "<< endl;
	output << "tar -xvf cmake-3.3.2.tar.gz && cd cmake-3.3.2          &&  \\ "<< endl;
	output << "cmake . -DCMAKE_USE_OPENSSL=ON -DCMAKE_INSTALL_PREFIX=/opt/mpact-dev-env/common_tools/cmake-3.3.2/					 &&  \\ "<< endl;
	output << "make -j8 install							 &&  \\ "<< endl;
	output << "mkdir -p /etc/modulefiles/cmake				 &&  \\ "<< endl;
	output << "touch /etc/modulefiles/cmake/3.3.2				 &&  \\ "<< endl;
	output << "echo \"#%Module\" >> ${CMAKE}					&&  \\ "<< endl;
	output << "echo \"set version 3.3.2\" >> ${CMAKE}				&&  \\ "<< endl;
	output << "echo \'set name \"MPACT Development Environment - 2.1.0\"\' >> ${CMAKE} &&  \\ "<< endl;
	output << "echo \'set msg \"Loads the development environment for MPACT.\"\' >> ${CMAKE}	&&  \\ "<< endl;
	output << "echo >> ${CMAKE}							&&  \\ "<< endl;
	output << "echo \"proc ModulesHelp { } {\" >> ${CMAKE}			&&  \\ "<< endl;
	output << "echo \" puts stderr \\$msg}\" >> ${CMAKE}			&&  \\ "<< endl;
	output << "echo >> ${CMAKE}							&&  \\ "<< endl;
	output << "echo \"module-whatis  \\$msg\" >> ${CMAKE}			&&  \\ "<< endl;
	output << "echo >> ${CMAKE}							&&  \\ "<< endl;
	output << "echo \"#Set the path to CMake/CTest/CPack\" >> ${CMAKE} &&  \\ "<< endl;
	output << "echo \"prepend-path PATH /opt/mpact-dev-env/common_tools/cmake-\\$version/bin\" >> ${CMAKE}		&&  \\ "<< endl;
	output << "rm -f cmake_3.3.*                         &&   \\ "<< endl;
	//if using mkl, writing module file (argv[3] is tpl url. Presumably, if vera_tpl is not used, mkl is being used)
	if (TPLs.find("vera") == string::npos) {
		output << "mkdir -p /etc/modulefiles/mkl && \\ " << endl;
		output << "touch /etc/modulefiles/mkl/2018 && \\ " << endl;
		output << "echo \"#%Module\" >> ${MKL}                  && \\ " << endl;
		output << "echo \"proc ModulesHelp {} {\" >> ${MKL}                      && \\ " << endl;
		output << "echo \"\t global version modroot\" >> ${MKL}         && \\ " << endl;
		output << "echo >> ${MKL}               && \\ " << endl;
		output <<  "echo \'puts stderr \"The MKL module enables use of the Intel optimized BLAS/LAPACK\"\' >> ${MKL}            && \\ " << endl;
		output << "echo \'puts stderr \"libraries included with MKL.\"\' >> ${MKL}      && \\ " << endl;
		output << "echo \'puts stderr \"\"\' >> ${MKL}                  && \\ " << endl;
		output << "echo \'puts stderr \"The following environment variables are defined:\"\' >> ${MKL}  && \\ " << endl;
		output << "echo \'puts stderr\"\"\' >> ${MKL}   && \\ " << endl;
		output << "echo \'puts stderr \"\\$MKL_LIB\"\' >> ${MKL}        && \\ " << endl;
		output << "echo \'puts stderr \"\\$MKL_INCLUDE\"\' >> ${MKL} && \\ " << endl;
		output << "echo \'puts stderr \"\\$MKLROOT\"\' >> ${MKL} && \\" << endl;
		output << "echo \'puts stderr \"\"\' >> ${MKL}  && \\ " << endl;
		output << "echo \'puts stderr \"These should be used to reference the include or library files at compile,\"\' >> ${MKL} && \\ " << endl;
		output << "echo \'puts stderr \"link, or run time. Examples of using MKL with the GNU compilers are\"\' >> ${MKL} && \\ " << endl;
		output << "echo \'puts stderr \"\"\' >> ${MKL}  && \\ " << endl;
		output << "echo \'puts stderr \"\\$ gcc -I\\$MKL_INC -L\\$MKL_LIB -l mkl_rt my_mkl.c\"\' >> ${MKL}      && \\ " << endl;
		output << "echo \'puts stderr \"\\$ gcc my_mkl.c -lmkl_intel -lmkl_intel_thread -lmkl_core -liomp5 -lpthread -lm\"\' >> ${MKL}  && \\ " << endl;
		output << "echo \'puts stderr \"\"\' >> ${MKL}          && \\ " << endl;
		output << "echo \'puts stderr \"Using MKL with the Intel compilers is easier\"\' >> ${MKL} && \\ " << endl;
		output << "echo \'puts stderr\"\"\' >> ${MKL}    && \\ " << endl;
		output << "echo \'puts stderr \"\\$ icc -mkl my_mkl.c\"\' >> ${MKL} && \\ " << endl;
		output << "echo \'puts stderr \"\"\' >> ${MKL}  && \\ " << endl;
		output << "echo \'puts stderr \"You may also wish to consult the Intel Link Line Advisor\"\' >> ${MKL}   && \\ " << endl;
		output << "echo \'puts stderr \"\"\' >> ${MKL}   && \\ " << endl;
		output << "echo \'puts stderr \"https://software.intel.com/en-us/articles/intel-mkl-link-line-advisor/\"\' >> ${MKL}   && \\ " << endl;
		output << "echo \'puts stderr \"\"\' >> ${MKL}   && \\ " << endl;
		output << "echo \"}\" >> ${MKL}     && \\ " << endl;
		output << "echo >> ${MKL}        && \\ " << endl;
		output << "echo \'module-whatis  \"Name: MKL\"\' >> ${MKL}      && \\ " << endl;
		output << "echo \'module-whatis  \"Version: 2018.0\"\' >> ${MKL}  && \\ " << endl;
		output << "echo \'module-whatis  \"Category: Library, Development, Core, BLAS, LAPACK\"\' >> ${MKL}      && \\ " << endl;
		output << "echo \'module-whatis  \"Description: Intel optimized BLAS/LAPACK libraries, also including\"\' >> ${MKL}      && \\ " << endl;
		output << "echo \'module-whatis  \"             FFT and other mathematical and statistical routines.\"\' >> ${MKL}       && \\ " << endl;
		output << "echo \'module-whatis  \"License information: https://software.intel.com/sites/default/files/managed/86/1d/Master_EULA_for_Intel_Sw_Development_Products.pdf\"\' >> ${MKL}  && \\ " << endl;
		output << "echo \'module-whatis  \"Package documentation: https://software.intel.com/en-us/articles/intel-math-kernel-library-documentation\"\' >> ${MKL}       && \\ " << endl;
		output << "echo \'setenv          MKLROOT         /opt/intel/mkl\' >> ${MKL}    && \\ " << endl;
		output << "echo \'setenv          MKL_INCLUDE     /opt/intel/mkl/include\' >> ${MKL}     && \\ " << endl;
		output << "echo \'setenv          MKL_LIB /opt/intel/mkl/lib/intel64\' >> ${MKL}         && \\ " << endl;
		output << "echo \'prepend-path    LD_LIBRARY_PATH /opt/intel/mkl/lib/intel64\' >> ${MKL}         && \\ " << endl;
		output << "echo \'prepend-path    LIBRARY_PATH /opt/intel/mkl/lib/intel64\' >> ${MKL} && \\ " << endl;
	}
	//cloning TPLs
	output << "cd /scratch && \\" << endl;
	output << "git clone " << TPLs << " && \\" << endl;
	//writing gcc module file
	output << "mkdir -p /etc/modulefiles/PrgEnv/mpact-dev/ && \\" << endl;
	output << "cd /etc/modulefiles/PrgEnv/mpact-dev/ && \\" << endl;
	output << "touch " << gccVersion << " && \\" << endl;
	output << "echo \"#%Module\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo  >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"set root ${DEVTOOL_INSTALL_DIR}\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo  \"set version ${GCC_VERSION}\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"set tpldir ${VERA_TPL_INSTALL_DIR}\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"set name \"\"MPACT Development Environment - \\$version\"\"\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"set msg \"\"Loads the development environment for MPACT.\"\"\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"proc ModulesHelp { } {\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo \" puts stderr \\$msg\" >> ${GCC_VERSION} && \\"  << endl;
	output << "echo \"}\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"module-whatis \\$msg\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"if ![ is-loaded \'mpi/" << mpiVersion << "-x86_64\'] {\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo \'\tmodule load mpi/" << mpiVersion << "-x86_64\' >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"}\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"if ![ is-loaded \'cmake/3.3.2'] {\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo \'\tmodule load cmake/3.3.2\' >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"}\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"setenv TRIBITS_DEV_ENV_BASE \\$root\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"setenv TRIBITS_DEV_ENV_GCC_VERSION \\$version\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"setenv TRIBITS_DEV_ENV_COMPILER_BASE \\$root/\\$version\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"#setenv TRIBITS_DEV_ENV_GCC_DIR\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"setenv TRIBITS_DEV_ENV_MPICH_DIR \\$env(MPI_HOME)\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"setenv LOADED_TRIBITS_DEV_ENV \\$version\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"setenv LOADED_VERA_DEV_ENV \\$version\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"prepend-path PATH \\$root/common_tools\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"#HDF5\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"set tplpath \\$tpldir/hdf5-1.8.10\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"setenv HDF5_ROOT \\$tplpath\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"prepend-path PATH \\$tplpath/bin\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"prepend-path LD_LIBRARY_PATH \\$tplpath/lib\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"prepend-path INCLUDE \\$tplpath/include\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"#BLAS/LAPACK\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"set tplpath \\$tpldir/lapack-3.3.1\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"setenv BLAS_ROOT \\$tplpath\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"setenv LAPACK_DIR \\$tplpath\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"prepend-path LD_LIBRARY_PATH \\$tplpath/lib\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo >> ${GCC_VERSION}&& \\" << endl;
	output << "echo \"#HYPRE\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"set tplpath \\$tpldir/hypre-2.9.1a\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"setenv HYPRE_DIR \\$tplpath\" >> ${GCC_VERSION} >> ${FINISH_BUILD} && \\" << endl;
	output << "echo \"prepend-path LD_LIBRARY_PATH \\$tplpath/lib\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"#PETSC\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"set tplpath \\$tpldir/petsc-3.5.4\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"setenv PETSC_DIR \\$tplpath\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"# setenv PETSC_ARCH linux-gnu-opt\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"prepend-path PATH \\$tplpath/bin\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"prepend-path LD_LIBRARY_PATH \\$tplpath/lib\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo >> \\${GCC_VERSION} && \\" << endl;
	output << "echo \"#SLEPC\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"set tplpath \\$tpldir/slepc-3.5.4\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"setenv SLEPC_DIR \\$tplpath\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"prepend-path LD_LIBRARY_PATH \\$tplpath/lib\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"#SUNDIALS\"\\ >> ${GCC_VERSION} && \\ " << endl;
	output << "echo \"set tplpath \\$tpldir/sundials-2.9.0\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"setenv SUNDIALS_DIR \\$tplpath\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"prepend-path LD_LIBRARY_PATH \\$tplpath/lib\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"set-alias gitdist-status {gitdist dist-repo-status}\" >> ${GCC_VERSION} && \\" << endl;
	output << "echo \"set-alias gitdist-mod {gitdist --dist-mod-only}\" >> ${GCC_VERSION} && \\" << endl;
	output << "#echo \"set-alias gitdist-mod-status {gitdist dist-repo-status --dist-mod-only}\" >> ${GCC_VERSION} && \\" << endl;
	//cleaning gcc module file (adding necessary quotation marks where echo commands weren't working)
	output << "sed -i \'s/set name MPACT Development Environment - $version/set name \"MPACT Development Environment -$version\"/g\' " << gccVersion << " && \\" << endl; 
	output << "sed -i \'s/Loads the development environment for MPACT./\"Loads the development environment for MPACT.\"/g\' " << gccVersion << " && \\" << endl;
	output << "rm -f *GCC* && \\" << endl;
	//writes script to complete image build. necessary for commands that must be run in an interactive shell
	//namely, conda create, source activate, and module load, which are necessary to run cmake and make
	output << "touch /scratch/finishBuild.sh && \\ " << endl;
	output << "chmod 755 /scratch/finishBuild.sh && \\ " << endl;
	output << "echo \'#!/bin/bash\' >> ${FINISH_BUILD} && \\ " << endl;
	output << "echo \'echo \'y\' | conda create -n Python27 python=2.7\' >> ${FINISH_BUILD} && \\" << endl;
	output << "echo \'source activate Python27\' >> ${FINISH_BUILD} && \\" << endl;
	output << "echo \'module load cmake\' >> ${FINISH_BUILD} && \\" << endl;
	output << "echo \'mkdir /scratch/tmp && cd /scratch/tmp\' >> ${FINISH_BUILD} && \\" << endl;
	output << "echo \'module load mpi\' >> ${FINISH_BUILD} && \\" << endl;
	output << "echo \'cmake  -D CMAKE_INSTALL_PREFIX=/opt/mpact-dev-env/" << gccVersion << "/tpls/  -D CMAKE_BUILD_TYPE=Release  -D CMAKE_CXX_COMPILER=mpicxx  -D CMAKE_C_COMPILER=mpicc  -D CMAKE_Fortran_COMPILER=mpif90  -D FFLAGS=\"-fPIC -O3\"  -D CFLAGS=\"-fPIC -O3\"  -D CXXFLAGS=\"-fPIC -O3\"  -D LDFLAGS=\"\"  -D ENABLE_SHARED=ON  -D PROCS_INSTALL=8 " << cmakeDir << "\' >> ${FINISH_BUILD} && \\" << endl;
	//the first make -j8 always fails, but the second one will succeed. 
	output << "echo \'make -j8 || \' >> ${FINISH_BUILD} && \\" << endl;
	output << "echo \'make -j8\' >> ${FINISH_BUILD} && \\"  << endl;
       	output << "echo \'cd /scratch && rm -rf tmp *_tpls TriBITS finishBuild.sh cmake-3.3.* && yum clean all\' >> ${FINISH_BUILD} && \\" << endl;
	output << "echo \'exit || exit\' >> ${FINISH_BUILD} && \\" << endl;
	output << "/bin/bash -i /scratch/finishBuild.sh && \\" << endl;
	output << "yum install -y redhat-lsb rpm-build rpm-sign check dejagnu expect && \\" << endl;
	output << "mkdir /scratch/buildGCC && cd /scratch/buildGCC && \\" << endl;
	output << "git clone https://gitlab.com/BobSteagall/gcc-builder.git && \\" << endl;
	output << "cd gcc-builder && \\" << endl;
	output << "git checkout gcc" << gccVersion[4] << " && \\" << endl;;
	string versionNumber;
	string versionNumNoDots;
	for (int i = 4; i < gccVersion.length(); ++i) {
	  versionNumber += gccVersion[i];
	  if (gccVersion[i] != '.') {
	    versionNumNoDots += gccVersion[i];
	  }
	}
	output << "sed -i \'s/GCC_VERSION=" << gccVersion[4] << ".X.0/GCC_VERSION=" << versionNumber << "/g\' ./gcc-build-vars.sh && \\" << endl;
	output << "/bin/bash -i /scratch/buildGCC/gcc-builder/build-gcc.sh -T && \\" << endl;
	output << "/bin/bash -i /scratch/buildGCC/gcc-builder/stage-gcc.sh && \\" << endl;
	output << "export PATH=/usr/local/gcc/" << versionNumber << "/bin:$PATH && \\" << endl;
	output << "export LD_LIBRARY_PATH=/usr/local/gcc/" << versionNumber << "/lib:/usr/local/gcc/" << versionNumber << "/lib64:$LD_LIBRARY_PATH && \\" << endl;
	output << "/bin/bash -i /scratch/buildGCC/gcc-builder/clean-gcc.sh" << endl;
	/////end writing Dockerfile

	//builds docker image from Dockerfile
	string name = argv[5];
	//full command: docker build -t NAME .
	string command = "docker build -t " + name + " .";	
	system(command.c_str());
	//argv[6] is zip instruction. if true, executes system command to save docker image as a .tar.gz
	if (!strcmp(argv[6], "true")) {
	  //full command: docker save NAME | gzip > NAME.tar.gz
	  command = "docker save " + name + " | gzip > " + name + ".tar.gz";
	  system(command.c_str());
 	}
}

