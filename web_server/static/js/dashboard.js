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


get_sensor_data('soil_humidity', 7).done((data) => {insert_line_chart('#soil_humidity_graph', data, 'soil_humidity')})
get_sensor_data('soil_temperature', 7).done((data) => {insert_line_chart('#soil_temperature_graph', data, 'soil_temperature')})
get_sensor_data('ph', 7).done((data) => {insert_line_chart('#soil_ph_graph', data, 'Soil pH')})
get_sensor_data('soil_humidity').done((data) => {insert_gauge_chart('soil_humidity_gauge', data, soil_moisture_sectors)})

//placeholder leaching likelihood gauge
insert_gauge_chart('soil_leaching_gauge', 45, soil_leaching_sectors)

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