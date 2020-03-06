import React, { Component } from "react";
import "./Ingredients.css";
import { Link } from "react-router-dom";

class Ingredients extends Component {
    constructor(props) {
        super(props);
        this.state = {
            numberOfGuests: this.props.model.getNumberOfGuests()
        };
    }

    // this methods is called by React lifecycle when the
    // component is actually shown to the user (mounted to DOM)
    // that's a good place to setup model observer
    componentDidMount() {
        this.props.model.addObserver(this);
    }

    // this is called when component is removed from the DOM
    // good place to remove observer
    componentWillUnmount() {
        this.props.model.removeObserver(this);
    }

    // in our update function we modify the state which will
    // cause the component to re-render
    update() {
        this.setState({
        numberOfGuests: this.props.model.getNumberOfGuests()
        });
    }
        
    render() {
        let ingredients_name = this.props.dish.extendedIngredients.map(ingred => (
            <p className="names">{ingred.name}</p>));
        let ingredients_amount = this.props.dish.extendedIngredients.map(ingred => (
            <p className="amounts">{ingred.amount*this.props.model.getNumberOfGuests()}</p>));
        let ingredients_unit = this.props.dish.extendedIngredients.map(ingred => (
            <p className="units">{ingred.unit}</p>));
        return (
            <div className="ingredients">
                <div className="ingredient_box_top">
                    <p id="textPeeps">Ingredients for {this.state.numberOfGuests} people</p>
                </div>
                <div className="ingredient_box_middle">
                    <ul id="namelist">{ingredients_name}</ul>
                    <ul id="amountlist">{ingredients_amount}</ul>
                    <ul id="unitlist">{ingredients_unit}</ul>
                </div>
                <div className="ingredient_box_bottom">
                    <Link to="/search">
                        <button className="button" id="addbtn" onClick={() => this.props.model.addDishToMenu(this.props.dish)}>
                            Add to Menu
                        </button>
                    </Link>

                </div>
            </div>
        );
    }
}
export default Ingredients;
