package com.chcd.xpsohijackdemo;

import android.os.Environment;
import android.util.Log;

import de.robv.android.xposed.IXposedHookLoadPackage;
import de.robv.android.xposed.XC_MethodHook;
import de.robv.android.xposed.callbacks.XC_LoadPackage;

import static de.robv.android.xposed.XposedHelpers.findAndHookMethod;

/**
 * Created by i-fengshuaihu on 2018/12/7.
 */

public class XpHookModule implements IXposedHookLoadPackage{
    private static String TAG = "CHCD_DEBUG";
    private static final String HOOKSOPATH = Environment.getDataDirectory()
            + "/data/com.chcd.xpsohijackdemo/lib/libhookSo.so";
    @Override
    public void handleLoadPackage(XC_LoadPackage.LoadPackageParam loadPackageParam) throws Throwable {
        if(loadPackageParam.packageName.equals("com.chcd.xpsohijackdemo")){
            Log.d(TAG, "enter target package:"  + loadPackageParam.packageName);
            findAndHookMethod(Runtime.class, "doLoad", String.class, ClassLoader.class, new XC_MethodHook() {
                @Override
                protected void beforeHookedMethod(MethodHookParam param) throws Throwable {
                    String name = (String) param.args[0];
                    Log.i(TAG, "Load so file: " + name);
                    if (param.hasThrowable() || name == null || !name.endsWith("libaddHello.so")) {
                        return;
                    }
                    param.args[0] = HOOKSOPATH;
                    Log.i(TAG, "Load so file: " + param.args[0]);
                }

                @Override
                protected void afterHookedMethod(MethodHookParam param) throws Throwable {

                }
            });
        }

    }
}
