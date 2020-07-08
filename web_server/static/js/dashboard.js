get_sensor_data = (sensor_type, period) => {
    return $.ajax({
        url: '/api/sensor_data',
        dataType: 'json',
        type: 'GET',
        data: {
            period: period,
            sensor_type: sensor_type
        }
    })
}

insert_line_chart = (chart_div, data, title) => {
    new Chart($(chart_div)[0].getContext('2d'), {
        // The type of chart we want to create
        type: 'line',
        // The data for our dataset
        data: {
            labels: data['date_time'],
            datasets: [{
                label: title,
                backgroundColor: 'rgb(255, 99, 132)',
                borderColor: 'rgb(255, 99, 132)',
                data: data['values']
            }]
        },

        // Configuration options go here
        options: {}
    });
}

insert_gauge_chart = (gauge_div, value) => {
    new JustGage({
        id: gauge_div,
        value: value,
        min: 0,
        max: 100,
        label: 'percent'
    })
}

get_sensor_data('soil_humidity', 7).done((data) => {insert_line_chart('#soil_humidity_graph', data, 'soil_humidity')})
get_sensor_data('soil_temperature', 7).done((data) => {insert_line_chart('#soil_temperature_graph', data, 'soil_temperature')})
get_sensor_data('ph', 7).done((data) => {insert_line_chart('#soil_ph_graph', data, 'Soil pH')})
get_sensor_data('soil_humidity').done((data) => {insert_gauge_chart('soil_humidity_gauge', data)})

//placeholder leaching likelihood gauge
insert_gauge_chart('soil_leaching_gauge', 67)

class SensorMap {
    constructor(map_div) {
        console.log(map_div)
        this.sensor_map = L.map(map_div).setView([-44.3970, 171.2550], 20)
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