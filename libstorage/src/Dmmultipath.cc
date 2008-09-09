/*
  Textdomain    "storage"
*/

#include <sstream>

#include "y2storage/Dmmultipath.h"
#include "y2storage/DmmultipathCo.h"
#include "y2storage/SystemCmd.h"
#include "y2storage/AppUtil.h"
#include "y2storage/Storage.h"

using namespace storage;
using namespace std;

Dmmultipath::Dmmultipath( const DmmultipathCo& d, unsigned nr, Partition* p ) :
	DmPart( d, nr, p )
    {
    y2milestone( "constructed dmmultipath %s on co %s", dev.c_str(),
		 cont->name().c_str() );
    }

Dmmultipath::~Dmmultipath()
    {
    y2debug( "destructed dmmultipath %s", dev.c_str() );
    }

string Dmmultipath::removeText( bool doing ) const
    {
    string txt;
    string d = dev.substr(12);
    if( p && p->OrigNr()!=p->nr() )
	d = co()->numToName(p->OrigNr());
    if( doing )
	{
	// displayed text during action, %1$s is replaced by multipath partition name e.g. pdc_dabaheedj1
	txt = sformat( _("Deleting multipath partition %1$s"), d.c_str() );
	}
    else
	{
	// displayed text before action, %1$s is replaced by multipath partition name e.g. pdc_dabaheedj1
	// %2$s is replaced by size (e.g. 623.5 MB)
	txt = sformat( _("Delete multipath partition %1$s (%2$s)"), d.c_str(),
		       sizeString().c_str() );
	}
    return( txt );
    }

string Dmmultipath::createText( bool doing ) const
    {
    string txt;
    string d = dev.substr(12);
    if( doing )
	{
	// displayed text during action, %1$s is replaced by multipath partition name e.g. pdc_dabaheedj1
	txt = sformat( _("Creating multipath partition %1$s"), d.c_str() );
	}
    else
	{
	if( mp=="swap" )
	    {
	    // displayed text before action, %1$s is replaced by multipath partition e.g. pdc_dabaheedj1
	    // %2$s is replaced by size (e.g. 623.5 MB)
	    txt = sformat( _("Create swap multipath partition %1$s (%2$s)"),
	                   d.c_str(), sizeString().c_str() );
	    }
	else if( !mp.empty() )
	    {
	    if( encryption==ENC_NONE )
		{
		// displayed text before action, %1$s is replaced by multipath partition e.g. pdc_dabaheedj1
		// %2$s is replaced by size (e.g. 623.5 MB)
		// %3$s is replaced by file system type (e.g. reiserfs)
		// %4$s is replaced by mount point (e.g. /usr)
		txt = sformat( _("Create multipath partition %1$s (%2$s) for %4$s with %3$s"),
			       d.c_str(), sizeString().c_str(), fsTypeString().c_str(),
			       mp.c_str() );
		}
	    else
		{
		// displayed text before action, %1$s is replaced by multipath partition e.g. pdc_dabaheedj1
		// %2$s is replaced by size (e.g. 623.5 MB)
		// %3$s is replaced by file system type (e.g. reiserfs)
		// %4$s is replaced by mount point (e.g. /usr)
		txt = sformat( _("Create encrypted multipath partition %1$s (%2$s) for %4$s with %3$s"),
			       d.c_str(), sizeString().c_str(), fsTypeString().c_str(),
			       mp.c_str() );
		}
	    }
	else if( p && p->type()==EXTENDED )
	    {
	    // displayed text before action, %1$s is replaced by multipath partition e.g. pdc_dabaheedj1
	    // %2$s is replaced by size (e.g. 623.5 MB)
	    txt = sformat( _("Create extended multipath partition %1$s (%2$s)"),
			   d.c_str(), sizeString().c_str() );
	    }
	else
	    {
	    // displayed text before action, %1$s is replaced by multipath partition e.g. pdc_dabaheedj1
	    // %2$s is replaced by size (e.g. 623.5 MB)
	    txt = sformat( _("Create multipath partition %1$s (%2$s)"),
			   d.c_str(), sizeString().c_str() );
	    }
	}
    return( txt );
    }

string Dmmultipath::formatText( bool doing ) const
    {
    string txt;
    string d = dev.substr(12);
    if( doing )
	{
	// displayed text during action, %1$s is replaced by multipath partition e.g. pdc_dabaheedj1
	// %2$s is replaced by size (e.g. 623.5 MB)
	// %3$s is replaced by file system type (e.g. reiserfs)
	txt = sformat( _("Formatting multipath partition %1$s (%2$s) with %3$s"),
		       d.c_str(), sizeString().c_str(), fsTypeString().c_str() );
	}
    else
	{
	if( !mp.empty() )
	    {
	    if( mp=="swap" )
		{
		// displayed text before action, %1$s is replaced by multipath partition e.g. pdc_dabaheedj1
		// %2$s is replaced by size (e.g. 623.5 MB)
		txt = sformat( _("Format multipath partition %1$s (%2$s) for swap"),
			       d.c_str(), sizeString().c_str() );
		}
	    else if( encryption==ENC_NONE )
		{
		// displayed text before action, %1$s is replaced by multipath partition e.g. pdc_dabaheedj1
		// %2$s is replaced by size (e.g. 623.5 MB)
		// %3$s is replaced by file system type (e.g. reiserfs)
		// %4$s is replaced by mount point (e.g. /usr)
		txt = sformat( _("Format multipath partition %1$s (%2$s) for %4$s with %3$s"),
			       d.c_str(), sizeString().c_str(), fsTypeString().c_str(),
			       mp.c_str() );
		}
	    else
		{
		// displayed text before action, %1$s is replaced by multipath partition e.g. pdc_dabaheedj1
		// %2$s is replaced by size (e.g. 623.5 MB)
		// %3$s is replaced by file system type (e.g. reiserfs)
		// %4$s is replaced by mount point (e.g. /usr)
		txt = sformat( _("Format encrypted multipath partition %1$s (%2$s) for %4$s with %3$s"),
			       d.c_str(), sizeString().c_str(), fsTypeString().c_str(),
			       mp.c_str() );
		}
	    }
	else
	    {
	    // displayed text before action, %1$s is replaced by multipath partition e.g. pdc_dabaheedj1
	    // %2$s is replaced by size (e.g. 623.5 MB)
	    // %3$s is replaced by file system type (e.g. reiserfs)
	    txt = sformat( _("Format multipath partition %1$s (%2$s) with %3$s"),
			   d.c_str(), sizeString().c_str(),
			   fsTypeString().c_str() );
	    }
	}
    return( txt );
    }

string Dmmultipath::resizeText( bool doing ) const
    {
    string txt;
    string d = dev.substr(12);
    if( doing )
        {
	if( needShrink() )
	    // displayed text during action, %1$s is replaced by multipath partition e.g. pdc_dabaheedj1
	    // %2$s is replaced by size (e.g. 623.5 MB)
	    txt = sformat( _("Shrinking multipath partition %1$s to %2$s"), d.c_str(), sizeString().c_str() );
	else
	    // displayed text during action, %1$s is replaced by multipath partition e.g. pdc_dabaheedj1
	    // %2$s is replaced by size (e.g. 623.5 MB)
	    txt = sformat( _("Extending multipath partition %1$s to %2$s"), d.c_str(), sizeString().c_str() );
	// text displayed during action
	txt += ' ' + _("(progress bar might not move)");
        }
    else
        {
	if( needShrink() )
	    // displayed text before action, %1$s is replaced by multipath partition e.g. pdc_dabaheedj1
	    // %2$s is replaced by size (e.g. 623.5 MB)
	    txt = sformat( _("Shrink multipath partition %1$s to %2$s"), d.c_str(), sizeString().c_str() );
	else
	    // displayed text before action, %1$s is replaced by multipath partition e.g. pdc_dabaheedj1
	    // %2$s is replaced by size (e.g. 623.5 MB)
	    txt = sformat( _("Extend multipath partition %1$s to %2$s"), d.c_str(), sizeString().c_str() );

        }
    return( txt );
    }

string Dmmultipath::setTypeText( bool doing ) const
    {
    string txt;
    string d = dev.substr(12);
    if( doing )
        {
        // displayed text during action, %1$s is replaced by partition name (e.g. pdc_dabaheedj1),
        // %2$s is replaced by hexadecimal number (e.g. 8E)
        txt = sformat( _("Setting type of multipath partition %1$s to %2$X"),
                      d.c_str(), id() );
        }
    else
        {
        // displayed text before action, %1$s is replaced by partition name (e.g. pdc_dabaheedj1),
        // %2$s is replaced by hexadecimal number (e.g. 8E)
        txt = sformat( _("Set type of multipath partition %1$s to %2$X"),
                      d.c_str(), id() );
        }
    return( txt );
    }

void Dmmultipath::getInfo( DmmultipathInfo& tinfo ) const
    {
    DmPart::getInfo( info );
    tinfo.p = info;
    }

namespace storage
{

std::ostream& operator<< (std::ostream& s, const Dmmultipath &p )
    {
    s << *(DmPart*)&p;
    return( s );
    }

}

bool Dmmultipath::equalContent( const Dmmultipath& rhs ) const
    {
    return( DmPart::equalContent(rhs) );
    }

void Dmmultipath::logDifference( const Dmmultipath& rhs ) const
    {
    DmPart::logDifference(rhs);
    }

Dmmultipath& Dmmultipath::operator= ( const Dmmultipath& rhs )
    {
    y2debug( "operator= from %s", rhs.nm.c_str() );
    *((DmPart*)this) = rhs;
    return( *this );
    }
