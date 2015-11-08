netCDF Explorer
====================

netCDF Explorer is a multi-platfrom graphical browser for the
[netCDF](http://www.unidata.ucar.edu/software/netcdf) file format,
including 
[DAP](http://opendap.org).

netCDF Explorer dependencies
------------

[wxWidgets](https://www.wxwidgets.org/)
wxWidgets is a library for creating graphical user interfaces for cross-platform applications.
<br /> 

[netCDF](http://www.unidata.ucar.edu/software/netcdf)
netCDF is a set of software libraries and self-describing, 
machine-independent data formats that support the creation, 
access, and sharing of array-oriented scientific data.
<br /> 

Building from source
------------

Install dependency packages (Ubuntu):
<br /> 

sudo apt-get install libwxgtk3.0-dev
<br /> 
sudo apt-get install libnetcdf-dev netcdf-bin netcdf-doc
<br /> 

Get source:
<br /> 

git clone https://github.com/pedro-vicente/netcdf-explorer.git
<br /> 

Build with:
<br /> 

autoreconf -vfi
<br /> 
./configure
<br /> 
make
<br /> 

Enjoy!
<br /> 

