import React, { Component } from "react";
import { withRouter, Link } from 'react-router-dom';
import modelInstance from "../data/DinnerModel";
import Ingredients from "../Ingredients/Ingredients.js";
import "./Details.css";

class Details extends Component {
    constructor(props) {
        super(props);

        this.state = {
            status: "LOADING"
        }
        this.pathname = this.props.location.pathname;
        this.dishId = this.pathname.substr(6, this.pathname.length - 6)
    }

    componentDidMount(){
        this.getDish();
    }
    getDish = () => {
        modelInstance
            .getDish(this.dishId)
            .then(dish => {
                this.setState({
                    status: "LOADED",
                    dish: dish
                })
            })
            .catch(() => {
                this.setState({
                    status: "ERROR"
                })
            })
    }
    
    render() {
        let img = null;
        let header = null;
        let prep = null;
        let ingred = null;
        switch(this.state.status){
            case "LOADING":
                img = <em className="details_image">Loading...</em>;
                header = <h1 className="Details_header">Loading...</h1>;
                prep = <em className="preparation_text">Loading...</em>;
                ingred = <em className="preparation_text">Loading...</em>;
                break;

            case "LOADED":
                img = <img 
                    className="details_image" 
                    src={"https://spoonacular.com/recipeImages/"+this.state.dish.id+"-556x370.jpg"} 
                    alt={this.state.dish.alt}>
                </img>;
                header=<h1 className="details_header">{this.state.dish.title}</h1>;
                prep = <div className="preparation_text">{this.state.dish.instructions}</div>
                ingred = <Ingredients dish={this.state.dish} model={this.props.model}/>
                break;

            default:
                img = <em>BIG ERROR</em>;
                break;
        }
        return (
            <div className="details">
                {header}
                {img}
                <h1 className="preparation">Preparation</h1>
                {prep}
                <Link id="backbtn" to="/search">
                    <button className="button">Back to search</button>
                </Link>
                {ingred}
            </div>
        );
    }
}
export default withRouter(Details);