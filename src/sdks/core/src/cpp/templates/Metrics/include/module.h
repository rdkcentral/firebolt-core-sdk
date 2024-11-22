#pragma once

#include "error.h"
/* ${IMPORTS} */

${if.declarations}namespace Firebolt {
namespace ${info.Title} {
${if.enums}

// Enums
/* ${ENUMS} */${end.if.enums}
${if.types}
// Types
/* ${TYPES} */${end.if.types}
${if.providers}/* ${PROVIDERS} */${end.if.providers}${if.xuses}/* ${XUSES} */${end.if.xuses}
${if.methods}struct I${info.Title} {

    virtual ~I${info.Title}() = default;
    virtual bool ready( Firebolt::Error *err = nullptr ) = 0 ;
    virtual bool signIn( Firebolt::Error *err = nullptr ) = 0 ;
    virtual bool signOut( Firebolt::Error *err = nullptr ) = 0 ;

    // Methods & Events
    /* ${METHODS:declarations} */
};${end.if.methods}

} //namespace ${info.Title}
}${end.if.declarations}





    
   

