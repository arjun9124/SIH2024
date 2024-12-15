# Constants
FARADAY_CONSTANT = 96485  # Faraday constant in C/mol
THERMONEUTRAL_VOLTAGE = 1.48  # Thermoneutral voltage in V
MOLAR_VOLUME = 22.4  # Molar volume of gas at STP in L/mol

# Function to calculate efficiencies
def calculate_efficiencies(time_seconds, applied_voltage, applied_current):
    """
    Calculate hydrogen production efficiency and energy efficiency based on bubble time.

    Parameters:
        time_seconds (float): Time in seconds for the bubble to travel 5 mL.
        applied_voltage (float): Voltage applied to the electrolyzer (in V).
        applied_current (float): Current applied to the electrolyzer (in A).

    Returns:
        dict: A dictionary with hydrogen production efficiency and energy efficiency.
    """
    # Volume of hydrogen experimentally measured (bubble volume in L)
    experimental_volume_h2 = 5 / 1000  # Convert mL to L

    # Experimental flow rate of hydrogen (in L/s)
    experimental_flow_rate = experimental_volume_h2 / time_seconds

    # Convert experimental flow rate to mol/s
    experimental_moles_h2 = experimental_flow_rate / MOLAR_VOLUME

    # Theoretical moles of hydrogen produced based on Faraday's law
    theoretical_moles_h2 = (applied_current * 1) / (2 * FARADAY_CONSTANT)

    # Hydrogen production efficiency
    hydrogen_efficiency = (experimental_moles_h2 / theoretical_moles_h2) * 100

    # Power input (W)
    power_input = applied_voltage * applied_current

    # Power used for actual hydrogen production
    power_used_for_h2 = experimental_moles_h2 * THERMONEUTRAL_VOLTAGE * FARADAY_CONSTANT

    # Energy efficiency
    energy_efficiency = (power_used_for_h2 / power_input) * 100

    return {
        "Hydrogen Production Efficiency (%)": hydrogen_efficiency,
        "Energy Efficiency (%)": energy_efficiency
    }

# Input from the user
def main():
    print("Hydrogen Production and Energy Efficiency Calculator")
    time_seconds = float(input("Enter time (in seconds) for bubble to travel 5 mL: "))
    applied_voltage = 12 #float(input("Enter applied voltage (in V): "))
    applied_current = 25 #float(input("Enter applied current (in A): "))

    # Calculate efficiencies
    efficiencies = calculate_efficiencies(time_seconds, applied_voltage, applied_current)

    # Display results
    print("\nResults:")
    print(f"Hydrogen Production Efficiency: {efficiencies['Hydrogen Production Efficiency (%)']:.2f}%")
    #print(f"Energy Efficiency: {efficiencies['Energy Efficiency (%)']:.2f}%")

if __name__ == "__main__":
    main()
