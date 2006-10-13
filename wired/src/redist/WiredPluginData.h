#ifndef __WIREDPLUGINDATA_H__
#define __WIREDPLUGINDATA_H__

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
   #include <wx/wx.h>
#endif

#include "WiredDocument.h"

class WiredDocument;


class WiredPluginData : public WiredDocument
{
public:
  WiredPluginData() {};
  ~WiredPluginData() {};

  /**
   * Implemented in WiredDocument class
   */

  //virtual void	 Load(WiredPluginData& Datas) {}
  //virtual void	 Save(WiredPluginData& Datas) {}


};

#endif //  __WIREDPLUGINDATA_H__
