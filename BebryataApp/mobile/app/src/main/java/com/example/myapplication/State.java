package com.example.myapplication;

public class State {
    private String name; // название магазина
    private int flagResource; // ресурс флага
    private double lat; //широта
    private double lon; //долгота
    private String address; //адрес магазина
    private double distance; //расстояние до магазина

    public State(String name, int flag, double lat, double lon, String address, double distance){

        this.name = name;
        this.flagResource = flag;
        this.lat = lat;
        this.lon = lon;
        this.address = address;
        this.distance = distance;
    }

    public String getName() {
        return this.name;
    }
    public void setName(String name) {
        this.name = name;
    }

    public int getFlagResource() {
        return this.flagResource;
    }
    public void setFlagResource(int flagResource) {
        this.flagResource = flagResource;
    }

    public double getLat() { return this.lat; }
    public void setLat(double lat) { this.lat = lat; }

    public double getLon() { return this.lon; }
    public void setLon(double lon) { this.lon = lon; }

    public String getAddress() { return this.address; }
    public void setAddress(String address) { this.address = address; }

    public double getDistance() { return this.distance; }
    public void setDistance(double distance) { this.distance = distance; }

}
