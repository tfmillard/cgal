#include <iostream>
#include <fstream>

#include <CGAL/IO/WKT.h>

#include <CGAL/Simple_cartesian.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

#include <boost/foreach.hpp>

#include <vector>

//TODO : If FT is Gmpq, the output of writing will not be doubles.
//typedef CGAL::Simple_cartesian<CGAL::Gmpq> Kernel;

typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;


int main(int argc, char* argv[])
{
  typedef CGAL::Point_2<Kernel> Point;
  typedef CGAL::Polygon_with_holes_2<Kernel> Polygon;
  typedef CGAL::Geometry_container<std::vector<Polygon>, boost::geometry::multi_polygon_tag> MultiPolygon;
  std::ifstream is((argc>1)?argv[1]:"data/polygons.wkt");
  std::list<Polygon> polys;
  do
  {
    Polygon p;
    CGAL::read_polygon_WKT(is, p);
    if(!p.outer_boundary().is_empty())
      polys.push_back(p);
  }while(is.good() && !is.eof());
  BOOST_FOREACH(Polygon p, polys)
      std::cout<<p<<std::endl;
  
  is = std::ifstream((argc>2)?argv[2]:"data/multipolygon.wkt");
  MultiPolygon mp;
  CGAL::read_multipolygon_WKT(is, mp);
  BOOST_FOREACH(Polygon p, mp)
    std::cout<<p<<std::endl;
}
