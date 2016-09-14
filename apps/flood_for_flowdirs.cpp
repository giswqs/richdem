#include <iostream>
#include <string>
#include <cstdlib>
#include "richdem/common/version.hpp"
#include "richdem/depressions/priority_flood.hpp"
#include "richdem/common/Array2D.hpp"
#include "richdem/flats/flat_resolution.hpp"
#include "richdem/methods/d8_methods.hpp"

template<class T>
int PerformAlgorithm(std::string filename, std::string outputname, std::string analysis){
  bool flipH = false; //TODO
  bool flipV = false;
  std::string flip = "noflip";

  if(flip=="fliph")
    flipH=true;
  else if(flip=="flipv")
    flipV=true;
  else if(flip=="fliphv")
    flipH=flipV=true;
  else if(flip!="noflip"){
    std::cerr<<"Unrecognised flip directive."<<std::endl;
    return -1;
  }

  Array2D<T> elevations(filename,false);

  //Flip tiles if the geotransform demands it
  if( (elevations.geotransform[1]<0) ^ flipH)
    elevations.flipHorz();
  if( (elevations.geotransform[5]>0) ^ flipV)
    elevations.flipVert();


  improved_priority_flood(elevations);
  
  elevations.printStamp(5);

  Array2D<uint8_t> flowdirs;

  barnes_flat_resolution_d8(elevations,flowdirs,false);

  flowdirs.printStamp(5);

  //Flip tiles if the geotransform demands it
  if( (flowdirs.geotransform[1]<0) ^ flipH)
    flowdirs.flipHorz();
  if( (flowdirs.geotransform[5]>0) ^ flipV)
    flowdirs.flipVert();

  flowdirs.printStamp(5);

  flowdirs.saveGDAL(outputname, analysis);

  return 0;
}

template< typename... Arguments >
int Router(std::string inputfile, Arguments ... args){
  switch(peekGDALType(inputfile)){
    case GDT_Byte:
      return PerformAlgorithm<uint8_t >(args...);
    case GDT_UInt16:
      return PerformAlgorithm<uint16_t>(args...);
    case GDT_Int16:
      return PerformAlgorithm<int16_t >(args...);
    case GDT_UInt32:
      return PerformAlgorithm<uint32_t>(args...);
    case GDT_Int32:
      return PerformAlgorithm<int32_t >(args...);
    case GDT_Float32:
      return PerformAlgorithm<float   >(args...);
    case GDT_Float64:
      return PerformAlgorithm<double  >(args...);
    case GDT_CInt16:
    case GDT_CInt32:
    case GDT_CFloat32:
    case GDT_CFloat64:
      std::cerr<<"Complex types are unsupported. Sorry!"<<std::endl;
      return -1;
    case GDT_Unknown:
    default:
      std::cerr<<"Unrecognised data type: "<<GDALGetDataTypeName(peekGDALType(inputfile))<<std::endl;
      return -1;
  }
}

int main(int argc, char **argv){
  std::string analysis = PrintRichdemHeader(argc, argv);
  
  if(argc!=3){
    std::cerr<<argv[0]<<" <Input filename> <Output filename>"<<std::endl;
    return -1;
  }

  Router(argv[1],argv[1],argv[2],analysis);

  return 0;
}