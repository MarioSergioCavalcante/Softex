import * as THREE from '../../libs/three/three.module.js';
import { OrbitControls } from '../../libs/three/jsm/OrbitControls.js';
import { GLTFLoader } from '../../libs/three/jsm/GLTFLoader.js';
import { Stats } from '../../libs/stats.module.js';
import { CanvasUI } from '../../libs/CanvasUI.js'
import { ARButton } from '../../libs/ARButton.js';
import {
	Constants as MotionControllerConstants,
	fetchProfile
} from '../../libs/three/jsm/motion-controllers.module.js';

const DEFAULT_PROFILES_PATH = 'https://cdn.jsdelivr.net/npm/@webxr-input-profiles/assets@1.0/dist/profiles';
const DEFAULT_PROFILE = 'generic-trigger';

class App{
	constructor(){
		const container = document.createElement( 'div' );
		document.body.appendChild( container );
        this.camera = new THREE.PerspectiveCamera(60, window.innerWidth/window.innerHeight, 0.1, 100);
        this.camera.position.set(0,0,2);


        this.scene = new THREE.Scene();
        this.scene.background = new THREE.Color(0xaaaaaa);

        const ambient = new THREE.HemisphereLight(0xffffff, 0xbbbbff, 0.3);
        this.scene.add(ambient);

        const light = new THREE.DirectionalLight();
        light.position.set(0.2, 1, 1);
        this.scene.add(light);

        this.renderer = new THREE.WebGLRenderer({antialias: true});
        this.renderer.setPixelRatio( window.devicePixelRatio);
        this.renderer.setSize(window.innerWidth, window.innerHeight);
        container.appendChild( this.renderer.domElement);

        this.renderer.setAnimationLoop( this.render.bind(this));

        this.loadExperiment();



        const controls = new OrbitControls(this.camera,this.renderer.domElement);

        this.setupXR();
        window.addEventListener('resize', this.resize.bind(this) );
	}
	loadExperiment(){
	        this.assetsPath = './';
    	    const loader = new GLTFLoader().setPath(this.assetsPath);
    		const self = this;

    		// Load a GLTF resource
    		loader.load(
    			// resource URL
    			`Aeroestabilizador.gltf`,
    			// called when the resource is loaded
    			function ( gltf ) {
    			    gltf.scene.castShadow=true;
                    self.scene.add(gltf.scene);
    			},
    			// called when loading data..
    			function ( loading ) {

    				console.log( 'loading' );

    			},
                // called when loading has errors
                function ( error ) {

                    console.log( 'An error happened' );

                 }
    		);
    		this.visible = false
    }
    setupXR(){
        navigator.xr.isSessionSupported( 'immersive-ar' ).then( ( supported ) => {

        				supported ? this.initScene : this.noARScene();

        			} );

    }
    initScene(){
        this.dummyCam = new THREE.Object3D();
        this.camera.add( this.dummyCam );
        this.mesh.position.set( 0, -0.5, -1.1 );
        this.camera.add( self.mesh );
    }
    noARScene(){

    }
    resize(){
        this.camera.aspect = window.innerWidth/window.innerHeight;
        this.camera.updateProjectionMatrix();
        this.renderer.setSize(window.innerWidth, window.innerHeight);
    }

	render( ) {
        this.renderer.render(this.scene, this.camera);
    }
}

export { App };