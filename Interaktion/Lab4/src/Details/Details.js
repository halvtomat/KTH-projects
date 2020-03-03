import React, { Component } from "react";
import "./Details.css";

class Details extends Component {
    constructor(props) {
        super(props);
    }
    
    render() {
        return (
        <div className="Details">
             <img 
              className="image" 
              src={"https://spoonacular.com/recipeImages/"+this.props.dishId+"-556x370.jpg"}> 
            </img>
        </div>
        );
    }
}

export default Details;
