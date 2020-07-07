get_sensor_data = (period) => {
    return $.ajax({
        url: '/api/sensor_data',
        dataType: 'json',
        type: 'GET',
        data: {
            period: period
        }
    })
}
get_sensor_data(7).done((data) => {insert_line_chart('#air_temperature', data, 'air_temperature')});
get_sensor_data(7).done((data) => {insert_line_chart('#air_humidity', data, 'air_humidity')})
get_sensor_data(7).done((data) => {insert_line_chart('#soil_humidity', data, 'soil_humidity')})
insert_line_chart = (chart_div, json_data, category) => {
    new Chart($(chart_div)[0].getContext('2d'), {
        // The type of chart we want to create
        type: 'line',
        // The data for our dataset
        data: {
            labels: json_data['data']['date_time'],
            datasets: [{
                label: category,
                backgroundColor: 'rgb(255, 99, 132)',
                borderColor: 'rgb(255, 99, 132)',
                data: json_data['data'][category]
            }]
        },

        // Configuration options go here
        options: {}
    });
}
insert_gauge_chart = (chart_div, json_data, category) => {
    new Chart($(chart_div)[0].getContext('2d'), {
        type: 'doughnut',

        // The data for our dataset
        data: {
            labels: ["January", "February", "March", "April", "May"],
            datasets: [{
                label: "My First dataset",
                backgroundColor: ['rgb(0, 99, 132)', 'green', 'red', 'yellow', 'orange'],
                borderColor: '#fff',
                data: [5, 10, 5, 2, 20],
            }]
        },

        // Configuration options go here
        options: {
            circumference: 1 * Math.PI,
            rotation: 1 * Math.PI,
            cutoutPercentage: 90
        }
    })
}
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