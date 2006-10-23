#ifndef __WIREDPLUGINDATA_H__
#define __WIREDPLUGINDATA_H__

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
   #include <wx/wx.h>
#endif

//#include "WiredDocument.h"


//class WiredDocument;

/**
 * WiredPluginData implements the WiredDocument class
 */
class WiredPluginData //: public WiredDocument
{
public:
  WiredPluginData() {};
  ~WiredPluginData() {};

  //From WiredDocument
  void	 Load(WiredPluginData& Datas);
  void	 Save(WiredPluginData& Datas);

};

#endif //  __WIREDPLUGINDATA_H__
