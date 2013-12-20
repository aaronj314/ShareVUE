// asproduct.h
#ifndef __AS_PRODUCT_H__
#define __AS_PRODUCT_H__

//////////////////////////////////////
//                                  //
//  Forward declared info pointer.  //
//                                  //
//  Contents are hidden and must    //
//  be accessed with accessors.     //
//                                  //
//////////////////////////////////////
struct as_product_info;
typedef struct as_product_info* as_product_ptr;

////////////////////////////////////////////////////////////////////////////////////
//                                                                                //
//  Read information based on a passed file name or executable path respectively  //
//                                                                                //
////////////////////////////////////////////////////////////////////////////////////
as_err_t  as_product_read_info( const char* info_file, as_product_ptr info );
as_err_t  as_product_find_and_read_info( const char* executable_path, as_product_ptr info );


//////////////////////////////////////
//                                  //
//  as_product_ptr ctors.           //
//                                  //
//  Does not read any information.  //
//                                  //
//////////////////////////////////////
as_err_t as_product_init_info( as_product_ptr* info );
void as_product_free_info( as_product_ptr* info );

/////////////////////////////////////
//                                 //
//  Get actual major product info  //
//                                 //
/////////////////////////////////////
const char* as_product_name( const as_product_ptr info );
const char* as_product_version( const as_product_ptr info );
const char* as_product_id( const as_product_ptr info );


typedef enum as_product_err {
    AS_PRODUCT_OK,
    AS_PRODUCT_VERSION_MISMATCH,
    AS_PRODUCT_COMPONENT_NOT_FOUND
} as_product_err_t;

/////////////////////////////////////////////////////////////////////
//                                                                 //
//  Given a component name and desired version, check for a match  //
//                                                                 //
//  found_version is set to what is found, regardless of whether   //
//  it matched.                                                    //
//                                                                 //
/////////////////////////////////////////////////////////////////////
as_product_err_t as_product_check_component_version( 
    as_product_ptr info,
    const char* component_name,
    const char* component_version,
    const char** found_version);

/////////////////////////////////////////////////////////////
//                                                         //
//  Create a major version string suitable for human eyes  //
//                                                         //
/////////////////////////////////////////////////////////////
int
as_product_printable_version( as_product_ptr info, const char** output );

#endif


