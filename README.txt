Drupal thisdayinhistory.module README.txt
==============================================================================

This module provides configurable blocks displaying past events that happened
on today's date (i.e., month/day). For example, if today was January 6th, it
might display the birth of Joan of Arc (born January 6, 1412).

BLOCKS:
- Any number of blocks can be created
- Events can be selected by taxonomy term, user, role and/or randomly
- A 'promote to block' field is also provided for content selection

EVENT IMPORTING:
Support for importing events is provided if the Node Import module is
installed.

PERMISSIONS:
The following permissions are provided:
- Administer
- Create
- Edit own
- Promote to block


Administration
------------------------------------------------------------------------------
Add/Delete/Configure Blocks:
  Administer > Site configuration > This Day in History > Configure blocks

Permissions:
  Administer › User management > Access control


Content Management
------------------------------------------------------------------------------
This Day in History module content consists of the Historical event node
type. Historical events are Drupal nodes and managed through standard
Drupal content management methods.

A Historical Event has the following fields:
- Title
- Date (Year / Month / Day)
- Event
- Promote to block


Notes on the Theming
------------------------------------------------------------------------------
- Blocks output the node teaser
- The blocks are designed for relatively short event descriptions. If you
  choose to go with longer events descriptions, you'll likely need custom
  block theming.
- The blocks don't use the node title in their output. This allows you to
  use the tolken module to create descriptive titles based on content if you 
  so choose.
- Theme functions are provided for full control of the block HTML.


Custom Block Theming
------------------------------------------------------------------------------
Changed in Drupal 6. Updated instructions coming.


Importing Content
------------------------------------------------------------------------------
Content importing is provided via the node_import module, which must be
installed seperately. The node_import module is available at:

  http://drupal.org/project/node_import

Importing notes:
- Content can be imported from a comma or tab seperated file
- The import_node module does not individually validate nodes, so it is
  possible to import content with an invalid date
- Four different date formats are supported:
    * yyyy-mm-dd    (e.g.: 2007-10-31 )
    * d/mm/yyyy     (e.g.: 31/10/2007 )
    * mm/d/yyyy     (e.g.: 10/31/2007 )
    * mmm d, yyyy   (e.g.: Oct 31, 2007 ) 
- The node_import module supports importing taxonomy


Date Support Notes
------------------------------------------------------------------------------
Drupal uses the native PHP date support, which is limited in the range of
years it can handle. The exact range depends on a number of factors. Some
modules are using the adodb date library to work around this. Unfortunately,
this is a seperate installation.

Since the "This Day in History" module has modest date handling requirements,
primarily on the display side, I've decided to not to require any additional
libraries. This means the date display is not configurable without custom
theming and data entry of the date field is more rigid than it would have
otherwise been.


Credits / Acknowledgements
------------------------------------------------------------------------------
The Quotes module provided much of starting point for this module. My thanks
go to authors and maintainers of that module.


Author / Maintainer
------------------------------------------------------------------------------
Dale McGladdery
dale at group42 dot ca
