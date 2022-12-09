package com.example.myapplication;

import static java.lang.Math.PI;
import static java.lang.Math.acos;
import static java.lang.Math.cos;
import static java.lang.Math.sin;

import android.Manifest;
import android.annotation.SuppressLint;
import android.content.ActivityNotFoundException;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.provider.MediaStore;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import java.io.BufferedReader;
import java.io.File;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Date;
import java.util.stream.Collectors;

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
    private Button plusCard;
    private TextView coords;
    private LocationManager locationManager;
    private ListView cardList;

    private static final int REQUEST_TAKE_PHOTO = 1;
    private ImageView imageView;
    private Uri outputFileUri;

    StringBuilder sGPS = new StringBuilder();

    ArrayList<State> states = new ArrayList<State>();


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        MyLocationListener.SetUpLocationListener(this);
        setContentView(R.layout.activity_main);


        checkLoc = findViewById(R.id.checkLoc);
        plusCard = findViewById(R.id.plusCard);
        coords = findViewById(R.id.coords);
        locationManager = (LocationManager) getSystemService(LOCATION_SERVICE);
        imageView = findViewById(R.id.im_png);
        cardList = findViewById(R.id.cardList);

        setInitialData();
        StateAdapter stateAdapter = new StateAdapter(this, R.layout.list_item, states);
        cardList.setAdapter(stateAdapter);

        checkLoc.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //startActivity(new Intent(Settings.ACTION_LOCATION_SOURCE_SETTINGS));
                showLocation(MyLocationListener.imHere);
            }
        });
        plusCard.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent takePhotoIntent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE); //
                try{
                    startActivityForResult(takePhotoIntent, REQUEST_TAKE_PHOTO);
                }catch (ActivityNotFoundException e){
                    e.printStackTrace();
                }
            }
        });
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == REQUEST_TAKE_PHOTO && resultCode == RESULT_OK) {
            // Фотка сделана, извлекаем миниатюру картинки
            Bundle extras = data.getExtras();
            Bitmap thumbnailBitmap = (Bitmap) extras.get("data");
            //imageView.setImageBitmap(thumbnailBitmap);
        }
    }
    @Override
    protected void onResume() {
        super.onResume();
        showLocation(MyLocationListener.imHere);
        setInitialData();
        StateAdapter stateAdapter = new StateAdapter(this, R.layout.list_item, states);
        cardList.setAdapter(stateAdapter);
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

    private void setInitialData() {
        if (!states.isEmpty())
        {
            states.clear();
        }
            //InputStream is = getResources().openRawResource(R.raw.shops);

            double latitude = MyLocationListener.imHere.getLatitude(); //текущая широта
            double longitude = MyLocationListener.imHere.getLongitude(); //текущая долгота
            double dis = 0; //расстояние до магазина
            ArrayList<State> states2 = new ArrayList<State>();

            dis = acos(sin(54.8395 * PI / 180) * sin(latitude * PI / 180) + cos(54.8395 * PI / 180) * cos(latitude * PI / 180) * cos(83.1068 * PI / 180 - longitude * PI / 180)) * 6372795;
            State el = new State("Красное&Белое", R.drawable.k_b, 54.8395, 83.1068, "Морской проспект 20, Советский район, Новосибирск", dis);
            states2.add(el);

            dis = acos(sin(54.86422 * PI / 180) * sin(latitude * PI / 180) + cos(54.86422 * PI / 180) * cos(latitude * PI / 180) * cos(83.08595 * PI / 180 - longitude * PI / 180)) * 6372795;
            el = new State("Красное&Белое", R.drawable.k_b, 54.86422, 83.08595, "Бульвар Молодёжи 15, Советский район, Новосибирск", dis);
            states2.add(el);

            dis = acos(sin(54.86 * PI / 180) * sin(latitude * PI / 180) + cos(54.86 * PI / 180) * cos(latitude * PI / 180) * cos(83.10868 * PI / 180 - longitude * PI / 180)) * 6372795;
            el = new State("Быстроном", R.drawable.bystr, 54.86, 83.10868, "3 Инженерная 5/1, Советский район, Новосибирск", dis);
            states2.add(el);

            dis = acos(sin(54.85995 * PI / 180) * sin(latitude * PI / 180) + cos(54.85995 * PI / 180) * cos(latitude * PI / 180) * cos(83.10498 * PI / 180 - longitude * PI / 180)) * 6372795;
            el = new State("Добрянка", R.drawable.dobr, 54.85995, 83.10498, "Кутателадзе 4/4, Советский район, Новосибирск", dis);
            states2.add(el);

            dis = acos(sin(54.86422 * PI / 180) * sin(latitude * PI / 180) + cos(54.86422 * PI / 180) * cos(latitude * PI / 180) * cos(83.08595 * PI / 180 - longitude * PI / 180)) * 6372795;
            el = new State("Пятёрочка", R.drawable.five, 54.86422, 83.08595, "Бульвар Молодёжи 15, Советский район, Новосибирск", dis);
            states2.add(el);

            dis = acos(sin(54.8533 * PI / 180) * sin(latitude * PI / 180) + cos(54.8533 * PI / 180) * cos(latitude * PI / 180) * cos(83.0387 * PI / 180 - longitude * PI / 180)) * 6372795;
            el = new State("Бристоль", R.drawable.k_b, 54.8533, 83.0387, "Миргородская 2-я 3, Советский район, Новосибирск", dis);
            states2.add(el);

            dis = acos(sin(54.85582 * PI / 180) * sin(latitude * PI / 180) + cos(54.85582 * PI / 180) * cos(latitude * PI / 180) * cos(83.05153 * PI / 180 - longitude * PI / 180)) * 6372795;
            el = new State("Бристоль", R.drawable.k_b, 54.85582, 83.05153, "Балтийская 35, Советский район, Новосибирск", dis);
            states2.add(el);

            dis = acos(sin(54.87048 * PI / 180) * sin(latitude * PI / 180) + cos(54.87048 * PI / 180) * cos(latitude * PI / 180) * cos(83.08829 * PI / 180 - longitude * PI / 180)) * 6372795;
            el = new State("Магнит", R.drawable.magn, 54.87048, 83.08829, "Гнесиных 10/1, Советский район, Новосибирск", dis);
            states2.add(el);

            dis = acos(sin(54.85259 * PI / 180) * sin(latitude * PI / 180) + cos(54.85259 * PI / 180) * cos(latitude * PI / 180) * cos(83.04546 * PI / 180 - longitude * PI / 180)) * 6372795;
            el = new State("Магнит", R.drawable.magn, 54.85259, 83.04546, "Шлюзовая 26а, Советский район, Новосибирск", dis);
            states2.add(el);

            dis = acos(sin(54.85011 * PI / 180) * sin(latitude * PI / 180) + cos(54.85011 * PI / 180) * cos(latitude * PI / 180) * cos(83.04499 * PI / 180 - longitude * PI / 180)) * 6372795;
            el = new State("Магнит", R.drawable.magn, 54.85011, 83.04499, "Добровольческая 6, Советский район, Новосибирск", dis);
            states2.add(el);

            dis = acos(sin(54.85995 * PI / 180) * sin(latitude * PI / 180) + cos(54.85995 * PI / 180) * cos(latitude * PI / 180) * cos(83.10498 * PI / 180 - longitude * PI / 180)) * 6372795;
            el = new State("Л'Этуаль", R.drawable.let, 54.85995, 83.10498, "Кутателадзе 4/4, Советский район, Новосибирск", dis);
            states2.add(el);


            double minDistance = 999999;
            int indexMinDistance = -1;
            while(!states2.isEmpty())
            {
                for (int i = 0; i < states2.size(); i++)
                {
                    if (states2.get(i).getDistance() < minDistance)
                    {
                        minDistance = states2.get(i).getDistance();
                        indexMinDistance = i;
                    }
                }
                states.add(states2.get(indexMinDistance));
                states2.remove(indexMinDistance);
                minDistance = 999999;
                indexMinDistance = -1;
            }

    }
    /**public void ScanningCode()
    {
        // The path to the resource directory.
        String dataDir = Utils.getDataDir(Barcode_Recognition.class) + "BarcodeReader/basic_features/";

        // Initialize barcode reader
        BarCodeReader reader = new BarCodeReader(dataDir + "CodeText.jpg");

        // read barcode of type Code39Extended
        for (BarCodeResult result : reader.readBarCodes()) {
            System.out.println("CodeText: " + result.getCodeText());
            System.out.println("Symbology type: " + result.getCodeType());
        }
    }*/
}

