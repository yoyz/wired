// Copyright (C) 2004-2006 by Wired Team
// Under the GNU General Public License Version 2, June 1991

#include "SeqTrackPattern.h"

SeqTrackPattern::SeqTrackPattern()
{

}

SeqTrackPattern::~SeqTrackPattern()
{
  std::vector<Pattern *>::iterator	it;

  for (it = Patterns.begin(); it != Patterns.end(); it++)
    delete *it;
}
