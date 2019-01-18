<template>
  <div class="about">
    <h1>Netwerk configuratie</h1>

    <b-alert variant="success" show v-if="wifi.status === 'connected'">
      De woordklok is op dit moment verbonden met het WiFi netwerk '{{ wifi.ssid }}'
    </b-alert>

    <h3>Beschikbare netwerken</h3>
    <b-table striped hover :items="networks" :fields="fields">
      <template slot="connect" slot-scope="network">
        <button>selecteer {{network.ssid}}</button>
      </template>
    </b-table>
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
    }
  },
  methods: {
    updateNetworks () {
      this.axios.get('/api/wifi/networks')
        .then(response => {
          this.networks = response.data
        })
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