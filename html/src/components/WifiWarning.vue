<template>
  <div class="alert alert-warning" role="alert" id="wifialert" v-if="wifi.status !== 'connected'">
    Let op! Op dit moment is de woord klok niet verbonden met een WiFi netwerk. Dit betekend dat de juiste tijd 
    niet opgehaald kan worden. Hierdoor kunnen ook functies als het instellen van kleuren niet goed werken. Ga
    naar de pagina <router-link to="/wifi">WiFi instellingen</router-link> om verbinding te maken.
  </div>
</template>

<script>
import { mapState } from 'vuex'

export default {
  name: 'WifiWarning',
  computed: mapState([ 'wifi' ]),
}

</script>