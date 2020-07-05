get_sensor_data = (column, period) => {
    return $.ajax({
        url: '/api/sensor_data',
        dataType: 'json',
        type: 'GET',
        data: {
            column: column,
            period: period
        }
    })
}
temp_promise = get_sensor_data('air_temperature', 7)
temp_promise.done((data) => {insert_chart('#chart1', data)});

insert_chart = (chart_div, json_data) => {
    new Chart($(chart_div)[0].getContext('2d'), {
        // The type of chart we want to create
        type: 'line',

        // The data for our dataset
        data: {
            labels: json_data['date_time_list'],
            datasets: [{
                label: 'Air Temperature',
                backgroundColor: 'rgb(255, 99, 132)',
                borderColor: 'rgb(255, 99, 132)',
                data: json_data['data_list']
            }]
        },

        // Configuration options go here
        options: {}
    });
}
class SensorMap {
    constructor(map_div) {
        console.log(map_div)
        this.sensor_map = L.map(map_div).setView([51.505, -0.09], 13)
        this.tile_layer = L.tileLayer('https://api.mapbox.com/styles/v1/{id}/tiles/{z}/{x}/{y}?access_token={accessToken}', {
        maxZoom: 18,
        id: 'baileyl/ckc6sxwfg1leg1hqd7jw7xmyf',
        tileSize: 512,
        zoomOffset: -1,
        accessToken: 'pk.eyJ1IjoiYmFpbGV5bCIsImEiOiJjandrNjUycDYwNWdqM3pwYnA4bW02bnh6In0.FDfyxDAJnM4ZR-VBxvuGOg'
        })
        this.tile_layer.addTo(this.sensor_map);
    }
    insert_geojson(geojson_object) {
        L.geoJSON(geojson_object).addTo(this.sensor_map)
    }
}

let sensor_map = new SensorMap('sensor_map')



sensors_geojson_promise = $.ajax({
        url: '/api/sensors_geojson',
        dataType: 'json',
        type: 'GET'
    })
sensors_geojson_promise.done((data) => {
    console.log(data)
    sensor_map.insert_geojson(data)
})