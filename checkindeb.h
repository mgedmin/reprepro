#ifndef __MIRRORER_CHECKINDEB_H
#define __MIRRORER_CHECKINDEB_H

#ifndef __MIRRORER_ERROR_H
#include "error.h"
#warning "What's hapening here?"
#endif
#ifndef __MIRRORER_DISTRIBUTION_H
#include "distribution.h"
#endif

struct debpackage {
	/* things to be set by deb_read: */
	char *package,*version,*source,*architecture;
	char *basename;
	char *control;
	/* things that might still be NULL then: */
	char *section;
	/* things that will still be NULL then: */
	char *component; //This might be const, too and save some strdups, but...
};
/* read the data from a .deb, make some checks and extract some data */
retvalue deb_read(struct debpackage **pkg, const char *filename);

/* do overwrites, add Filename, Size and md5sum to the control-item */
retvalue deb_complete(struct debpackage *pkg, const char *filekey, const char *md5andsize);
void deb_free(struct debpackage *pkg);

/* Insert the given control-chunk in the database, including all
 * files in the database and registering them */
retvalue checkindeb_addChunk(DB *packagesdb, DB *referencesdb,DB *filesdb, const char *identifier,const char *mirrordir,const char *chunk,const char *packagename,const char *filekey,const struct strlist *filekeys,const struct strlist *md5sums,const struct strlist *oldfilekeys);

/* insert the given .deb into the mirror in <component> in the <distribution>
 * putting things with architecture of "all" into <architectures> (and also
 * causing error, if it is not one of them otherwise)
 * ([todo:]if component is NULL, using translation table <guesstable>)
 * ([todo:]using overwrite-database <overwrite>)*/
retvalue deb_add(const char *dbdir,DB *references,DB *filesdb,const char *mirrordir,const char *component,struct distribution *distribution,const char *debfilename,int force);
#endif