<template>
  <div class="about">
    <h1>Netwerk configuratie</h1>

    <b-alert variant="success" show v-if="wifi.status === 'connected'">
      De woordklok is op dit moment verbonden met het WiFi netwerk '{{ wifi.ssid }}'
    </b-alert>

    <h3>Beschikbare netwerken</h3>
    <b-table striped hover :items="networks" :fields="fields">
      <template slot="connect" slot-scope="data">
        <button v-on:click="select(data.item)">selecteer</button>
      </template>
    </b-table>

    <br><br>

    <h3>Verbinden met netwerk</h3>
    <div class="form-group row">
      <label for="ssid" class="col-sm-2 col-form-label">SSID</label>
      <input type="text" class="col-sm-10 form-control" id="ssid" v-model="ssid">
    </div>
    <div class="form-group row">
      <label for="password" class="col-sm-2 col-form-label">Wachtwoord</label>
      <input type="password" class="col-sm-10 form-control" id="password" v-model="password">
    </div>

    <br />
    <button v-on:click="connect" class="btn btn-primary" >Verbinden</button>
    <br />
  </div>
</template>

<script>
import { mapState } from 'vuex'

export default {
  name: 'Wifi',
  computed: mapState([ 'wifi' ]),
  data () {
    return {
      networks: [],
      fields: [
        { key: 'ssid', label: 'SSID' },
        { key: 'rssi', label: "Signaalsterkte" },
        { key: 'channel', label: "Kanaal" },
        { key: 'encryption', label: 'Beveiliging' },
        { key: 'connect', label: 'Verbinden' }
      ],
      ssid: "",
      password: ""
    }
  },
  methods: {
    updateNetworks () {
      this.axios.get('/api/wifi/networks')
        .then(response => {
          this.networks = response.data
        })
    },
    select: function(network) {
      this.ssid = network.ssid
    },
    connect: function() {
      if (this.ssid.length) {
        this.axios.get('/api/wifi/connect', { params: {
          ssid: this.ssid,
          password: this.password
        }})
      }
    }
  },
  beforeDestroy () {
    clearInterval(this.polling)
  },
  created () {
    this.polling = setInterval(() => {
      this.updateNetworks()
    }, 60000)
    this.updateNetworks()
  }
}
</script>