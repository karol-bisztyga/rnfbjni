package com.rnfbjni;

import android.os.Bundle;

import com.facebook.react.ReactActivity;
import com.facebook.react.ReactActivityDelegate;
import com.facebook.react.ReactRootView;
import com.swmansion.gesturehandler.react.RNGestureHandlerEnabledRootView;

import expo.modules.splashscreen.singletons.SplashScreen;
import expo.modules.splashscreen.SplashScreenImageResizeMode;

import com.facebook.react.ReactInstanceManager;
import com.facebook.react.turbomodule.core.CallInvokerHolderImpl;
import com.facebook.react.bridge.ReactContext;

public class MainActivity extends ReactActivity implements ReactInstanceManager.ReactInstanceEventListener {

    static {
        System.loadLibrary("my_jni_module");
    }

  @Override
  protected void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    // SplashScreen.show(...) has to be called after super.onCreate(...)
    // Below line is handled by '@expo/configure-splash-screen' command and it's discouraged to modify it manually
    SplashScreen.show(this, SplashScreenImageResizeMode.CONTAIN, ReactRootView.class, false);
  }

    @Override
    public void onResume() {
        super.onResume();
        getReactInstanceManager().addReactInstanceEventListener(this);
    }

    @Override
    public void onPause() {
        super.onPause();
        getReactInstanceManager().removeReactInstanceEventListener(this);
    }
    /**
     * Returns the name of the main component registered from JavaScript.
     * This is used to schedule rendering of the component.
     */
    @Override
    protected String getMainComponentName() {
        return "main";
    }

    @Override
    protected ReactActivityDelegate createReactActivityDelegate() {
        return new ReactActivityDelegate(this, getMainComponentName()) {
            @Override
            protected ReactRootView createRootView() {
                return new RNGestureHandlerEnabledRootView(MainActivity.this);
            }
        };
    }

    @Override
    public void onReactContextInitialized(ReactContext context) {
        CallInvokerHolderImpl holder = (CallInvokerHolderImpl)context.getCatalystInstance().getJSCallInvokerHolder();
        install(context.getJavaScriptContextHolder().get());
    }

    public native void install(long jsContextNativePointer);
}
