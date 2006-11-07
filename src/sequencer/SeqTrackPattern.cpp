// Copyright (C) 2004-2006 by Wired Team
// Under the GNU General Public License Version 2, June 1991

#include "SeqTrackPattern.h"
#include "SequencerGui.h"

SeqTrackPattern::SeqTrackPattern()
{

}

SeqTrackPattern::~SeqTrackPattern()
{
  std::vector<Pattern *>		vectorCopy;
  std::vector<Pattern *>::iterator	it;

  // we must copy vector, because DeletePattern will delete some iterators
  vectorCopy = Patterns;
  for (it = vectorCopy.begin(); it != vectorCopy.end(); it++)
    SeqPanel->DeletePattern(*it);
}
