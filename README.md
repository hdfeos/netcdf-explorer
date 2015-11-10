netCDF Explorer
====================

netCDF Explorer is a multi-platfrom graphical browser for the
[netCDF](http://www.unidata.ucar.edu/software/netcdf) file format,
including 
[DAP](http://opendap.org).

Dependencies
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
GNU autoconf is used


Install dependency packages (Ubuntu):
<pre>
sudo apt-get install libwxgtk3.0-dev
sudo apt-get install libnetcdf-dev netcdf-bin netcdf-doc
</pre>

Get source and switch to release branch:
<pre>
git clone https://github.com/pedro-vicente/netcdf-explorer.git
git checkout release
</pre>

Build with:
<pre>
./configure
make
</pre>

Optional for ./configure (when building wxWidgets or netCDF from source):
<pre>
--with-wx-config=PATH   Use the given PATH to wx-config
--with-nc-config=PATH   Use the given PATH to nc-config
</pre>

Enjoy!
