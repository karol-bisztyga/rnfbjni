package com.rnfbjni;

import android.util.Log;

import com.facebook.react.bridge.ReactContext;
import com.facebook.react.turbomodule.core.CallInvokerHolderImpl;

public class MyHybrid {

    public void doIt(ReactContext context) {
        CallInvokerHolderImpl holder = (CallInvokerHolderImpl)context.getCatalystInstance().getJSCallInvokerHolder();
        long contextPointer = context.getJavaScriptContextHolder().get();
        initHybrid(contextPointer, holder);
    }

    public native void initHybrid(long jsContextNativePointer, CallInvokerHolderImpl jsCallInvokerHolder);
}
