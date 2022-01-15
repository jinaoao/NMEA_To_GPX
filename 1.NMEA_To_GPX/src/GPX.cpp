#include <iostream>
#include "../inc/GPX.h"
using namespace std;

GPX::GPX()
{}

//get method
string GPX::getOpen()
{
    return string(_GPX_HEAD);
}

string GPX::getClose()
{
    return string(_GPX_TAIL);
}

string GPX::getMetaData()
{
    string localstr(_GPX_META_HEAD);
    if(_metaName.length() > 0)
    {
        localstr += string(_GPX_NAME_HEAD);
        localstr += wrapCDATA(_metaName);
        localstr += string(_GPX_NAME_TAIL);
    }
    if(_metaDesc.length() > 0)
    {
        localstr += string(_GPX_DESC_HEAD);
        localstr += wrapCDATA(_metaDesc);
        localstr += string(_GPX_DESC_TAIL);
    }
    localstr += string(_GPX_META_TAIL);
    return localstr;
}

string GPX::getTrackOpen()
{
    return string(_GPX_TRAK_HEAD);
}

string GPX::getTrackClose()
{
    return string(_GPX_TRAK_TAIL);
}

string GPX::getTrackSegOpen()
{
    return string(_GPX_TRKSEG_HEAD);
}

string GPX::getTrackSegClose()
{
    return string(_GPX_TRKSEG_TAIL);
}

string GPX::getInfo()
{
    string localStr("");
    if (_name.length() > 0){
    localStr += _GPX_NAME_HEAD;
    localStr += wrapCDATA(_name);
    localStr += _GPX_NAME_TAIL;
  }
  if (_desc.length() > 0){
    localStr += _GPX_DESC_HEAD;
    localStr += wrapCDATA(_desc);
    localStr += _GPX_DESC_TAIL;
  }
  return localStr;
}

string GPX::getPt(string typ, string lat, string lon,string ele, string date, string time){
  string localStr(_GPX_PT_HEAD);
  localStr += lat + "\" lon=\"";
  localStr += lon + "\">\n";

  localStr += _GPX_TIME_HEAD;
  localStr += date + "T";
  localStr += time + "Z";
  localStr += _GPX_TIME_TAIL;

  if (ele.length() > 0){
    localStr += _GPX_ELE_HEAD;
    localStr += ele;
    localStr += _GPX_ELE_TAIL;
  }
  if (_sym.length() > 0){
    localStr += _GPX_SYM_HEAD;
    localStr += _sym;
    localStr += _GPX_SYM_TAIL;
  }
  if (_src.length() > 0){
    localStr += _GPX_SRC_HEAD;
    localStr += wrapCDATA(_src);
    localStr += _GPX_SRC_TAIL;
  }
  localStr += string(_GPX_PT_TAIL);
  return localStr;
}

//Set Methods
void GPX::setMetaName(string name){
  _metaName = name;
}
void GPX::setMetaDesc(string desc){
  _metaDesc = desc;
}
void GPX::setName(string name){
  _name = name;
}
void GPX::setDesc(string desc){
  _desc = desc;
}
void GPX::setSym(string sym){
  _sym = sym;
}
void GPX::setSrc(string src){
  _src = src;
}

//Private Functions
string GPX::wrapCDATA(string input){
  string localStr("");
  localStr += input;
  localStr += "";

  return localStr;
}
