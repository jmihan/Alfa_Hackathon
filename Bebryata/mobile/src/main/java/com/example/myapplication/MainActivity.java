package com.example.myapplication;

import android.Manifest;
import android.annotation.SuppressLint;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;
import android.provider.Settings;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import java.util.Date;

class MyLocationListener implements LocationListener {

    static Location imHere; // здесь будет всегда доступна самая последняя информация о местоположении пользователя.

    @SuppressLint("MissingPermission")
    public static void SetUpLocationListener(Context context) // это нужно запустить в самом начале работы программы
    {
        LocationManager locationManager = (LocationManager)
                context.getSystemService(Context.LOCATION_SERVICE);

        LocationListener locationListener = new MyLocationListener();

        locationManager.requestLocationUpdates(
                LocationManager.GPS_PROVIDER,
                0,
                10,
                locationListener); // здесь можно указать другие более подходящие вам параметры

        imHere = locationManager.getLastKnownLocation(LocationManager.GPS_PROVIDER);
    }

    @Override
    public void onLocationChanged(Location loc) {
        imHere = loc;
    }

    @Override
    public void onProviderDisabled(String provider) {
    }

    @Override
    public void onProviderEnabled(String provider) {
    }

    @Override
    public void onStatusChanged(String provider, int status, Bundle extras) {
    }
}
public class MainActivity extends AppCompatActivity {

    private Button checkLoc;
    private TextView coords;
    private LocationManager locationManager;
    StringBuilder sGPS = new StringBuilder();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        MyLocationListener.SetUpLocationListener(this);
        setContentView(R.layout.activity_main);


        checkLoc = findViewById(R.id.checkLoc);
        coords = findViewById(R.id.coords);
        locationManager = (LocationManager) getSystemService(LOCATION_SERVICE);


        checkLoc.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //startActivity(new Intent(Settings.ACTION_LOCATION_SOURCE_SETTINGS));
                showLocation(MyLocationListener.imHere);
            }
        });
    }

    @Override
    protected void onResume() {
        super.onResume();
        showLocation(MyLocationListener.imHere);
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED && ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_COARSE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
            // TODO: Consider calling
            //    ActivityCompat#requestPermissions
            // here to request the missing permissions, and then overriding
            //   public void onRequestPermissionsResult(int requestCode, String[] permissions,
            //                                          int[] grantResults)
            // to handle the case where the user grants the permission. See the documentation
            // for ActivityCompat#requestPermissions for more details.
            return;
        }
        //locationManager.requestLocationUpdates(LocationManager.GPS_PROVIDER, 0, 10, locationListener);
    }

    private void showLocation(Location location) {
        if (location == null) {
            return;
        }
        if (location.getProvider().equals(LocationManager.GPS_PROVIDER)) {
            coords.setText(formatLocation(location));
        }
    }

    private String formatLocation(Location location) {
        if (location == null) {
            return "";
        }
        return String.format("Coordinates: lat = %1$.4f, lon = %2$.4f, time = %3$tF %3$tT", location.getLatitude(), location.getLongitude(), new Date(location.getTime()));
    }


}

