

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0595 */
/* at Fri Jun 28 22:04:01 2013
 */
/* Compiler settings for MainUI.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0595 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __MainUI_h_h__
#define __MainUI_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMainUI_FWD_DEFINED__
#define __IMainUI_FWD_DEFINED__
typedef interface IMainUI IMainUI;

#endif 	/* __IMainUI_FWD_DEFINED__ */


#ifndef __MainUI_FWD_DEFINED__
#define __MainUI_FWD_DEFINED__

#ifdef __cplusplus
typedef class MainUI MainUI;
#else
typedef struct MainUI MainUI;
#endif /* __cplusplus */

#endif 	/* __MainUI_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __MainUI_LIBRARY_DEFINED__
#define __MainUI_LIBRARY_DEFINED__

/* library MainUI */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_MainUI;

#ifndef __IMainUI_DISPINTERFACE_DEFINED__
#define __IMainUI_DISPINTERFACE_DEFINED__

/* dispinterface IMainUI */
/* [uuid] */ 


EXTERN_C const IID DIID_IMainUI;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("A999E970-850C-484C-926C-B720F4DF4CD3")
    IMainUI : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IMainUIVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMainUI * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMainUI * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMainUI * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMainUI * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMainUI * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMainUI * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMainUI * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IMainUIVtbl;

    interface IMainUI
    {
        CONST_VTBL struct IMainUIVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMainUI_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMainUI_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMainUI_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMainUI_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IMainUI_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IMainUI_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IMainUI_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IMainUI_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_MainUI;

#ifdef __cplusplus

class DECLSPEC_UUID("6DA093B9-25B0-41AD-888E-F3C7C3ED7879")
MainUI;
#endif
#endif /* __MainUI_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


