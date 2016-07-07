GLT (Generic Lightweight Threads). 
Common API for Lightweight Thread Implementations.

 Developed by:
      Adrian Castello (adcastel@uji.es) at Universitat Jaume I
 Supervised by:
      Antonio J. Peña (antonio.pena@bsc.es) at Barcelona Supercomputing Center
      Rafael Mayo Gual and Enrique S. Quintana-Ortí ({mayo,quintana}@uji.es)
      Sangmin Seo and Pavan Balaji ({sseo,balaji}@anl.gov) at Argonne National 
      Laboratory

--------------------------------------------------------------------------------

			GLT Release 2.0

GLT is a common API for HPC lightweight thread (LWT) libraries. It supports 
MassiveThreads, Qthreads, and Argobots as underlying LWT solutions. 
Moreover, GLT over Pthread is implemented with comparative purpose. 

In addition, GLT can be used as POSIX threads API since version 2.0.   

1. Getting Started
2. How to use GLT
3. How to cite GLT
4. Reporting Problems

-------------------------------------------------------------------------------

1. Getting Started
==================

The following instructions take you through a sequence of steps to get
GLT installed and compiled.

(a) You will need the following prerequisites.

    - REQUIRED: This tar file GLT-1.0.tar.gz

    - REQUIRED: A C compiler (gcc is sufficient)

    - REQUIRED: An Argobots library installation

    - REQUIRED: A Qthreads library installation

    - REQUIRED: A MassiveThreads library installation
    
(b) Unpack the tar file and go to the top level directory:

      tar xzf GLT-2.0.tar.gz
      cd GLT 

    If your tar doesn't accept the z option, use

      gunzip GLT-2.0.tar.gz
      tar xf GLT-2.0.tar
      cd GLT

(c) Define environment variables:

    The definition of the HOME_ARG, HOME_QTH, and HOME_MTH environment 
    variables with the path to Argobots, Qthreads, and MassiveThreads 
    libraries respectively is required.

(d) Build GLT:

    cd src

    for csh and tcsh:

      make [arg|qth|mth|pth] |& tee m.txt

    for bash and sh:

      make [arg|qth|mth|pth] 2>&1 | tee m.txt

-------------------------------------------------------------------------

2. How to use GLT
===================

I. GLT offers two library approaches:

(a) Dynamic library. Once the step 1 is completed, a libglt.so file 
can be found in each underlying library folder. The glt.h file needs to 
be included in the user's code and the -lglt flag added to the 
compilation order.

(d) Static library. In order to use this performance-oriented 
implementation fast_glt.h file may be included in the user's code and 
the -DFASTGLT flag added to the compilation order.

II. Using Pthreads API with GLT

GLT also offers the use of code written with pthreads just including 
"glt_pthreads.h" instead of "pthread.h"


-------------------------------------------------------------------------

3. How to cite GLT
===================

To cite GLT in your work, please use the following for now:
A. Castelló, A.J. Peña, S. Seo, R. Mayo, P. Balaji, E.S. Quintana-Ortí.
GLT: A common API for lightweight thread libraries. 
www.hpca.uji.es/GLT. 2016

-------------------------------------------------------------------------

4. Reporting Problems
=====================

If you have problems with the installation or usage of GLT, please
send an email to adcastel@uji.es.

