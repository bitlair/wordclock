<template>
  <div class="hueSlider">
    <input type="range" min="0" max="255" class="form-control-range" id="formControlRange" v-bind:value="value"
      v-on:change="$emit('input', $event.target.value)"> {{ value }}
  </div>
</template>

<script>
export default {
  name: 'HueSlider',
  props: [ 'value' ]
}
</script>