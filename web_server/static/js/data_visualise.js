const soil_moisture_sectors = {
    percents: true,
    ranges: [{
        color : "#d9534f",
        lo : 0,
        hi : 25
    },
    {
        color: "#f0ad4e",
        lo: 25,
        hi: 50
    },
    {
        color : "#5cb85c",
        lo : 50,
        hi : 75
    },
    {
        color : "#d9534f",
        lo : 75,
        hi : Infinity
    }]
}

const soil_leaching_sectors = {
    percents: true,
    ranges: [{
        color : "#d9534f",
        lo : 80,
        hi : 100
    },
    {
        color: "#f0ad4e",
        lo: 60,
        hi: 80
    },
    {
        color: "#5cb85c",
        lo: 0,
        hi: 60
    }]
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

insert_gauge_chart = (gauge_div, value, sectors) => {
    new JustGage({
        id: gauge_div,
        value: value,
        min: 0,
        max: 100,
        label: 'percent',
        customSectors: sectors
    })
}